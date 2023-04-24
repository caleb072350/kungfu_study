from ctypes import *

class XSPEED_L1_ANILIANG(Structure):
    _fields_ = [
        ("exchangeID", c_char * 3),
        ("validFlag", c_uint8),
        ("instrumentID", c_char * 7),
        ("updateTime", c_char * 9),
        ("updateMillisec", c_int),
        
    ]
    _pack_ = 1