# matrixfall
用C语言实现的从上到下掉落字母效果的程序.在linux上可用.

## 使用方法(Usage)
    1. git clone <...> 
    2. Using CLion Open it
    3. Change content of msg.txt with you loved words , And save it using encoding of utf-8
    3. Enjoy it
## 关键点(KeyPoint)
    1. 获取当前shell窗口的 `宽度` 和 `高度`  tput rows / tput lines
    2. 为了保存以前的输出结果，使用了缓冲区
