7767517
119 140
Input                    input                    0 1 input
Convolution              Conv__174                1 1 input Conv__174:0 0=16 1=3 3=2 15=1 16=1 5=1 6=432
PReLU                    PRelu_1                  1 1 Conv__174:0 p_re_lu_1/Alpha_dequantize_prelu/add:0 0=16
Split                    splitncnn_0              1 2 p_re_lu_1/Alpha_dequantize_prelu/add:0 p_re_lu_1/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_1/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise                1 1 p_re_lu_1/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise:0 0=16 1=3 4=1 6=144 7=16
Convolution              Conv__177                1 1 depthwise:0 Conv__177:0 0=16 1=1 5=1 6=256
BinaryOp                 add_1                    2 1 p_re_lu_1/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__177:0 add_1:0
PReLU                    PRelu_2                  1 1 add_1:0 p_re_lu_2/Alpha_dequantize_prelu/add:0 0=16
Split                    splitncnn_1              1 2 p_re_lu_2/Alpha_dequantize_prelu/add:0 p_re_lu_2/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_2/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_1              1 1 p_re_lu_2/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_1:0 0=16 1=3 4=1 6=144 7=16
Convolution              Conv__184                1 1 depthwise_1:0 Conv__184:0 0=16 1=1 5=1 6=256
BinaryOp                 add_2                    2 1 p_re_lu_2/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__184:0 add_2:0
PReLU                    PRelu_3                  1 1 add_2:0 p_re_lu_3/Alpha_dequantize_prelu/add:0 0=16
Split                    splitncnn_2              1 2 p_re_lu_3/Alpha_dequantize_prelu/add:0 p_re_lu_3/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_3/Alpha_dequantize_prelu/add:0_splitncnn_1
Pooling                  max_pooling2d_1          1 1 p_re_lu_3/Alpha_dequantize_prelu/add:0_splitncnn_1 max_pooling2d_1:0 1=2 2=2 5=1
Padding                  channel_padding_1        1 1 max_pooling2d_1:0 channel_padding_1:0 8=16
ConvolutionDepthWise     depthwise_2              1 1 p_re_lu_3/Alpha_dequantize_prelu/add:0_splitncnn_0 depthwise_2:0 0=16 1=3 3=2 15=1 16=1 6=144 7=16
Convolution              Conv__197                1 1 depthwise_2:0 Conv__197:0 0=32 1=1 5=1 6=512
BinaryOp                 add_3                    2 1 channel_padding_1:0 Conv__197:0 add_3:0
PReLU                    PRelu_4                  1 1 add_3:0 p_re_lu_4/Alpha_dequantize_prelu/add:0 0=32
Split                    splitncnn_3              1 2 p_re_lu_4/Alpha_dequantize_prelu/add:0 p_re_lu_4/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_4/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_3              1 1 p_re_lu_4/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_3:0 0=32 1=3 4=1 6=288 7=32
Convolution              Conv__198                1 1 depthwise_3:0 Conv__198:0 0=32 1=1 5=1 6=1024
BinaryOp                 add_4                    2 1 p_re_lu_4/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__198:0 add_4:0
PReLU                    PRelu_5                  1 1 add_4:0 p_re_lu_5/Alpha_dequantize_prelu/add:0 0=32
Split                    splitncnn_4              1 2 p_re_lu_5/Alpha_dequantize_prelu/add:0 p_re_lu_5/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_5/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_4              1 1 p_re_lu_5/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_4:0 0=32 1=3 4=1 6=288 7=32
Convolution              Conv__205                1 1 depthwise_4:0 Conv__205:0 0=32 1=1 5=1 6=1024
BinaryOp                 add_5                    2 1 p_re_lu_5/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__205:0 add_5:0
PReLU                    PRelu_6                  1 1 add_5:0 p_re_lu_6/Alpha_dequantize_prelu/add:0 0=32
Split                    splitncnn_5              1 2 p_re_lu_6/Alpha_dequantize_prelu/add:0 p_re_lu_6/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_6/Alpha_dequantize_prelu/add:0_splitncnn_1
Pooling                  max_pooling2d_2          1 1 p_re_lu_6/Alpha_dequantize_prelu/add:0_splitncnn_1 max_pooling2d_2:0 1=2 2=2 5=1
Padding                  channel_padding_2        1 1 max_pooling2d_2:0 channel_padding_2:0 8=32
ConvolutionDepthWise     depthwise_5              1 1 p_re_lu_6/Alpha_dequantize_prelu/add:0_splitncnn_0 depthwise_5:0 0=32 1=3 3=2 15=1 16=1 6=288 7=32
Convolution              Conv__218                1 1 depthwise_5:0 Conv__218:0 0=64 1=1 5=1 6=2048
BinaryOp                 add_6                    2 1 channel_padding_2:0 Conv__218:0 add_6:0
PReLU                    PRelu_7                  1 1 add_6:0 p_re_lu_7/Alpha_dequantize_prelu/add:0 0=64
Split                    splitncnn_6              1 2 p_re_lu_7/Alpha_dequantize_prelu/add:0 p_re_lu_7/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_7/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_6              1 1 p_re_lu_7/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_6:0 0=64 1=3 4=1 6=576 7=64
Convolution              Conv__219                1 1 depthwise_6:0 Conv__219:0 0=64 1=1 5=1 6=4096
BinaryOp                 add_7                    2 1 p_re_lu_7/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__219:0 add_7:0
PReLU                    PRelu_8                  1 1 add_7:0 p_re_lu_8/Alpha_dequantize_prelu/add:0 0=64
Split                    splitncnn_7              1 2 p_re_lu_8/Alpha_dequantize_prelu/add:0 p_re_lu_8/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_8/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_7              1 1 p_re_lu_8/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_7:0 0=64 1=3 4=1 6=576 7=64
Convolution              Conv__226                1 1 depthwise_7:0 Conv__226:0 0=64 1=1 5=1 6=4096
BinaryOp                 add_8                    2 1 p_re_lu_8/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__226:0 add_8:0
PReLU                    PRelu_9                  1 1 add_8:0 p_re_lu_9/Alpha_dequantize_prelu/add:0 0=64
Split                    splitncnn_8              1 2 p_re_lu_9/Alpha_dequantize_prelu/add:0 p_re_lu_9/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_9/Alpha_dequantize_prelu/add:0_splitncnn_1
Pooling                  max_pooling2d_3          1 1 p_re_lu_9/Alpha_dequantize_prelu/add:0_splitncnn_1 max_pooling2d_3:0 1=2 2=2 5=1
Padding                  channel_padding_3        1 1 max_pooling2d_3:0 channel_padding_3:0 8=64
ConvolutionDepthWise     depthwise_8              1 1 p_re_lu_9/Alpha_dequantize_prelu/add:0_splitncnn_0 depthwise_8:0 0=64 1=3 3=2 15=1 16=1 6=576 7=64
Convolution              Conv__239                1 1 depthwise_8:0 Conv__239:0 0=128 1=1 5=1 6=8192
BinaryOp                 add_9                    2 1 channel_padding_3:0 Conv__239:0 add_9:0
PReLU                    PRelu_10                 1 1 add_9:0 p_re_lu_10/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_9              1 2 p_re_lu_10/Alpha_dequantize_prelu/add:0 p_re_lu_10/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_10/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_9              1 1 p_re_lu_10/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_9:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__240                1 1 depthwise_9:0 Conv__240:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_10                   2 1 p_re_lu_10/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__240:0 add_10:0
PReLU                    PRelu_11                 1 1 add_10:0 p_re_lu_11/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_10             1 2 p_re_lu_11/Alpha_dequantize_prelu/add:0 p_re_lu_11/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_11/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_10             1 1 p_re_lu_11/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_10:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__247                1 1 depthwise_10:0 Conv__247:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_11                   2 1 p_re_lu_11/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__247:0 add_11:0
PReLU                    PRelu_12                 1 1 add_11:0 p_re_lu_12/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_11             1 2 p_re_lu_12/Alpha_dequantize_prelu/add:0 p_re_lu_12/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_12/Alpha_dequantize_prelu/add:0_splitncnn_1
Pooling                  max_pooling2d_4          1 1 p_re_lu_12/Alpha_dequantize_prelu/add:0_splitncnn_1 max_pooling2d_4:0 1=2 2=2 5=1
ConvolutionDepthWise     depthwise_11             1 1 p_re_lu_12/Alpha_dequantize_prelu/add:0_splitncnn_0 depthwise_11:0 0=128 1=3 3=2 15=1 16=1 6=1152 7=128
Convolution              Conv__260                1 1 depthwise_11:0 Conv__260:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_12                   2 1 max_pooling2d_4:0 Conv__260:0 add_12:0
PReLU                    PRelu_13                 1 1 add_12:0 p_re_lu_13/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_12             1 2 p_re_lu_13/Alpha_dequantize_prelu/add:0 p_re_lu_13/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_13/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_12             1 1 p_re_lu_13/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_12:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__261                1 1 depthwise_12:0 Conv__261:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_13                   2 1 p_re_lu_13/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__261:0 add_13:0
PReLU                    PRelu_14                 1 1 add_13:0 p_re_lu_14/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_13             1 2 p_re_lu_14/Alpha_dequantize_prelu/add:0 p_re_lu_14/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_14/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_13             1 1 p_re_lu_14/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_13:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__268                1 1 depthwise_13:0 Conv__268:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_14                   2 1 p_re_lu_14/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__268:0 add_14:0
PReLU                    PRelu_15                 1 1 add_14:0 p_re_lu_15/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_14             1 3 p_re_lu_15/Alpha_dequantize_prelu/add:0 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_1 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_2
Pooling                  max_pooling2d_5          1 1 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_2 max_pooling2d_5:0 1=2 2=2 5=1
Split                    splitncnn_15             1 2 max_pooling2d_5:0 max_pooling2d_5:0_splitncnn_0 max_pooling2d_5:0_splitncnn_1
ConvolutionDepthWise     depthwise_16             1 1 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_16:0 0=128 1=3 3=2 15=1 16=1 6=1152 7=128
Convolution              Conv__287                1 1 depthwise_16:0 Conv__287:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_23                   2 1 max_pooling2d_5:0_splitncnn_1 Conv__287:0 add_23:0
PReLU                    PRelu_16                 1 1 add_23:0 p_re_lu_26/Alpha_dequantize_prelu/add:0 0=128
Convolution              Conv__288                1 1 p_re_lu_26/Alpha_dequantize_prelu/add:0 Conv__288:0 0=32 1=1 5=1 6=4096
PReLU                    PRelu_17                 1 1 Conv__288:0 p_re_lu_27/Alpha_dequantize_prelu/add:0 0=32
Split                    splitncnn_16             1 2 p_re_lu_27/Alpha_dequantize_prelu/add:0 p_re_lu_27/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_27/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_18             1 1 p_re_lu_27/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_18:0 0=32 1=3 4=1 6=288 7=32
Convolution              Conv__291                1 1 depthwise_18:0 Conv__291:0 0=32 1=1 5=1 6=1024
BinaryOp                 add_24                   2 1 p_re_lu_27/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__291:0 add_24:0
PReLU                    PRelu_18                 1 1 add_24:0 p_re_lu_28/Alpha_dequantize_prelu/add:0 0=32
Convolution              Conv__298                1 1 p_re_lu_28/Alpha_dequantize_prelu/add:0 Conv__298:0 0=1 1=3 3=3 5=1 6=288
Reshape                  Conv2D_24__141           1 1 Conv__298:0 conv2d_31 0=1 1=1 2=1
ConvolutionDepthWise     depthwise_14             1 1 p_re_lu_15/Alpha_dequantize_prelu/add:0_splitncnn_0 depthwise_14:0 0=128 1=3 3=2 15=1 16=1 6=1152 7=128
Convolution              Conv__299                1 1 depthwise_14:0 Conv__299:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_15                   2 1 max_pooling2d_5:0_splitncnn_0 Conv__299:0 add_15:0
PReLU                    PRelu_19                 1 1 add_15:0 p_re_lu_16/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_17             1 2 p_re_lu_16/Alpha_dequantize_prelu/add:0 p_re_lu_16/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_16/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_15             1 1 p_re_lu_16/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_15:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__300                1 1 depthwise_15:0 Conv__300:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_16                   2 1 p_re_lu_16/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__300:0 add_16:0
PReLU                    PRelu_20                 1 1 add_16:0 p_re_lu_17/Alpha_dequantize_prelu/add:0 0=128
Split                    splitncnn_18             1 2 p_re_lu_17/Alpha_dequantize_prelu/add:0 p_re_lu_17/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_17/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_17             1 1 p_re_lu_17/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_17:0 0=128 1=3 4=1 6=1152 7=128
Convolution              Conv__307                1 1 depthwise_17:0 Conv__307:0 0=128 1=1 5=1 6=16384
BinaryOp                 add_17                   2 1 p_re_lu_17/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__307:0 add_17:0
PReLU                    PRelu_21                 1 1 add_17:0 p_re_lu_18/Alpha_dequantize_prelu/add:0 0=128
Convolution              Conv__314                1 1 p_re_lu_18/Alpha_dequantize_prelu/add:0 Conv__314:0 0=32 1=1 5=1 6=4096
PReLU                    PRelu_22                 1 1 Conv__314:0 p_re_lu_19/Alpha_dequantize_prelu/add:0 0=32
Split                    splitncnn_19             1 2 p_re_lu_19/Alpha_dequantize_prelu/add:0 p_re_lu_19/Alpha_dequantize_prelu/add:0_splitncnn_0 p_re_lu_19/Alpha_dequantize_prelu/add:0_splitncnn_1
ConvolutionDepthWise     depthwise_19             1 1 p_re_lu_19/Alpha_dequantize_prelu/add:0_splitncnn_1 depthwise_19:0 0=32 1=3 4=1 6=288 7=32
Convolution              Conv__317                1 1 depthwise_19:0 Conv__317:0 0=32 1=1 5=1 6=1024
BinaryOp                 add_18                   2 1 p_re_lu_19/Alpha_dequantize_prelu/add:0_splitncnn_0 Conv__317:0 add_18:0
PReLU                    PRelu_23                 1 1 add_18:0 p_re_lu_20/Alpha_dequantize_prelu/add:0 0=32
Convolution              Conv__324                1 1 p_re_lu_20/Alpha_dequantize_prelu/add:0 Conv__324:0 0=1404 1=3 3=3 5=1 6=404352
Reshape                  Conv2D_25__173           1 1 Conv__324:0 output 0=1404 1=1 2=1
