from ctypes import *

class XSPEED_L1_ANILIANG(Structure):
    _fields_ = [
        ("exchangeID", c_char * 3),
        ("validFlag", c_uint8),
        ("instrumentID", c_char * 7),
        ("updateTime", c_char * 9),
        ("updateMillisec", c_int),
        ('lastPrice', c_double),
        ('matchAmount', c_int),
        ('matchTotalMoney', c_double),
        ('openInterest', c_double),
        ('buyPrice1', c_double),
        ('buyAmount1', c_int),
        ('sellPrice1', c_double),
        ('sellAmount1', c_int),
    ]
    _pack_ = 1