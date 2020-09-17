std_msgs/Header header 

# Режим работы системы управления движением
# TRANSPARENT_MODE = 0 «прозрачный» режим работы СУД (пересылка в БУД поступающих извне сообщений типа rtp_msgs/RTPMovCtrlCmd)
# AUTO_MODE = 1 автономный режим работы СУД
uint8 mcs_mode
uint8 TRANSPARENT_MODE = 0
uint8 AUTO_MODE = 1
