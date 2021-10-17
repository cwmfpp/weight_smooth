#include <string.h>
#include <stdio.h>

#define WIGHT_VALUE     5
#define S_DATA_WIDTH    40
#define S_INPUT_DATA_WIDTH   (S_DATA_WIDTH + WIGHT_VALUE - 1) 
#define ALIGN_SIZE      32
void weight_smooth(unsigned int *input_data, unsigned int *output_data, int data_len, int c, int h, int w)
{
    int s_input_data_len = ((44 * 44 * 4 - 1) / 32) * 32;
    int s_output_data_len = ((40* 40 * 4 - 1) / 32) * 32;
    unsigned int local_input_data[s_input_data_len] = {0};
    unsigned int local_output_data[s_output_data_len] = {0};
    unsigned int local_weight[] = {
        1, 2, 3, 2, 1,
        2, 4, 6, 4, 2,
        3, 6, 9, 6, 3,
        2, 4, 6, 4, 2,
        1, 2, 3, 2, 1
    };
    for (int i = 0; i < sizeof(local_weight) / sizeof(unsigned int); i++) {
        local_weight[i] = local_weight[i] / 81;
    }
    
    for (int _c = 0; _c < c; _c++) {
        for (int _h = 0; _h < h ; _h += 40) {
            for (int _w = 0; _w < w; _w = _w + 40) {
                printf("%d %s _w=%d w=%d add ============================ \n", __LINE__, __FUNCTION__, _w, w);
                for (int _s_h = 0; _s_h < 44; _s_h++) {
                    #if 1
                    printf("%d %s _s_h=%d _h=%d _w=%d h=%d w=%d\n", __LINE__, __FUNCTION__, _s_h, _h, _w, h, w);
                        int _v_h = 0;

                        if ((_h + _s_h - 2) > 0) {
                            _v_h = _h + _s_h -2;
                        } else {
                            _v_h = _h + _s_h;
                        }
                        if(_v_h > (h - 1)) {
                            _v_h = h - 1;
                        }
                    if (0 == _w) {
                        #if 0
                        int _v_h = 0;

                        if ((_h + _s_h - 2) > 0) {
                            _v_h = _h + _s_h -2;
                        } else {
                            _v_h = _h + _s_h;
                        }
                        if(_v_h > (h - 1)) {
                            _v_h = h - 1;
                        }
                        #endif
                        //_v_h = _h;
                        local_input_data[_s_h * 44 + 0] = input_data[_v_h * w];
                    //printf("%d %s _s_h=%d _h=%d _w=%d h=%d w=%d\n", __LINE__, __FUNCTION__, _s_h, _h, _w, h, w);
                        local_input_data[_s_h * 44 + 1] = input_data[_v_h * w];
                    //printf("%d %s _s_h=%d _h=%d _w=%d h=%d w=%d\n", __LINE__, __FUNCTION__, _s_h, _h, _w, h, w);
                        memcpy(local_input_data + _s_h * 44 + 2, input_data + _v_h * w, 42 * sizeof(unsigned int));
                    //printf("%d %s _s_h=%d _h=%d _w=%d h=%d w=%d\n", __LINE__, __FUNCTION__, _s_h, _h, _w, h, w);
                        //printf("%d %s _s_h=%d input_data[%d * %d] = %d\n", __LINE__, __FUNCTION__, _s_h, _h, w, input_data[_h * w]);
                    } else if((_w + 40) == w) {
                        #if 0
                        int _v_h = 0;

                        if ((_h + _s_h - 2) > 0) {
                            _v_h = _h + _s_h -2;
                        } else {
                            _v_h = _h + _s_h;
                        }
                        if(_v_h > (h - 1)) {
                            _v_h = h - 1;
                        }
                        #endif
                        printf("%d %s _v_h=%d\n", __LINE__, __FUNCTION__, _v_h);
                        memcpy(local_input_data + _s_h * 44, input_data + _v_h * w + _w - 2, 42 * sizeof(unsigned int));
                        local_input_data[_s_h * 44 + 42] = local_input_data[_s_h * 44 + 41];
                        local_input_data[_s_h * 44 + 43] = local_input_data[_s_h * 44 + 41];
                    } else {
                        #if 0
                        int _v_h = 0;

                        if ((_h + _s_h - 2) > 0) {
                            _v_h = _h + _s_h -2;
                        } else {
                            _v_h = _h + _s_h;
                        }
                        if(_v_h > (h - 1)) {
                            _v_h = h - 1;
                        }
                        #endif
                        memcpy(local_input_data + _s_h * 44, input_data + _v_h * w + _w - 2, 44 * sizeof(unsigned int));
                    }
                    //printf("%d %s _s_h=%d _h=%d _w=%d h=%d w=%d\n", __LINE__, __FUNCTION__, _s_h, _h, _w, h, w);
                    #endif
                }
                #if 1
                for(int i = 0; i < 44; i++) {
                    for (int j = 0; j < 44; j++) {
                        printf("%5d,", local_input_data[i * 44 + j]);
                    }
                    printf("\n");
                }
                #endif
            }
        }
    }

}


int main()
{
//void weight_smooth(unsigned int *input_data, unsigned int *output_data, int data_len, int c, int h, int w)
#define TMP_WIDTH   120 
    unsigned int input_data[TMP_WIDTH*TMP_WIDTH] = {0};
    unsigned int output_data[TMP_WIDTH*TMP_WIDTH];

    for (int i = 0; i < TMP_WIDTH; i++) {
        for (int j = 0; j < TMP_WIDTH; j++) {
            input_data[i * TMP_WIDTH + j] = i * TMP_WIDTH + j;//(i / 40) * (TMP_WIDTH / 40) + j /40 + 1;
        }
    }

    for (int i = 0; i < TMP_WIDTH; i++) {
        for (int j = 0; j < TMP_WIDTH; j++) {
            printf("%5d,", input_data[i * TMP_WIDTH + j]);//input_data[i * TMP_WIDTH + j] = (i / 40) * (TMP_WIDTH / 40) + j /40;
            if (0 == ((j + 1)% 40)) {
                printf(" = ");
            }
        }
        if (0 == ((i + 1) % 40)) {
            printf("\n");
            printf(" =====================================================================================================");
        }
        printf("\n");
    }
    weight_smooth(input_data, output_data, TMP_WIDTH*TMP_WIDTH, 1, TMP_WIDTH, TMP_WIDTH);
    return 0;
}