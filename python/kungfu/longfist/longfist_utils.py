import ctypes
import datetime

import longfist_constants as lf
import longfist_structs_sniffer as structs 

cast_data = lambda x, y: ctypes.cast(x, ctypes.POINTER(y)).contents

cast_frame = lambda f: cast_data(f.get_data(), structs.MsgType2LFStruct[f.msg_type()])

dcast_frame = lambda f: cast_frame(f) if f.msg_type() in structs.MsgType2LFStruct else None

def write(writer, struct, source=0, last_flag=True, request_id=-1):
    data = ctypes.addressof(struct)
    length = ctypes.sizeof(struct)
    msg_type = structs.LFStruct2MsgType[type(struct)]
    writer.write(data, length, source, msg_type, last_flag, request_id)

def get_contents(frame):
    '''
    :param frame: data frame in yjj
    :return:
        [(field, content1), (field, content2), ...]
    '''
    data = cast_frame(frame)
    return get_contents_d(data)

def get_contents_d(data):
    res = []
    if structs.DataFieldMap.has_key(data.__class__.__name__):
        for field_name, field_type in data._fields_:
            tp_s = structs.DataFieldMap[data.__class__.__name__][field_name]
            if type(tp_s) is dict:
                type_s = 't'
                content = tp_s.get(getattr(data, field_name), 'UnExpected')
            else:
                type_s = tp_s
                content = getattr(data, field_name)
            res.append((field_name, type_s, content))
        return res
    else:
        for field_name, field_type in data._fields_:
            res.append((field_name, field_type, getattr(data, field_name)))
        return res
    
def _byteify(data, ignore_dicts = False):
    # if this is a unicode string, return its string representation
    if isinstance(data, unicode):
        return data.encode('utf-8')
    # if this is a list of values, return list of byteified values
    if isinstance(data, list):
        return [_byteify(item, ignore_dicts=True) for item in data]
    # is this is a dictionary, return dictionary of byteified keys and values
    # but only if we haven't already byteified it
    if isinstance(data, dict) and not ignore_dicts:
        return dict((_byteify(key, ignore_dicts=True), _byteify(value, ignore_dicts=True)) for key, value in data.iteritems())
    # if it's anything else, return it in its original form
    return data

class ID2Exchange:
    SSE_CODE = 'SSE'
    SZE_CODE = 'SZE'

    @staticmethod
    def get_stock_exchange(ticker):
        if ticker.startswith('6'):
            return ID2Exchange.SSE_CODE
        else:
            return ID2Exchange.SZE_CODE

def process_position(positions):
    tickers = set().union(* [k.keys() for k in positions.values()])
    investor_position = {ticker: {lf.LfPosiDirectionType.Net:(positions["net_total"].get(ticker, 0), positions["net_yd"].get(ticker, 0)) for ticker in tickers} for _, positions in positions.items()}
    return investor_position

def strfnano(nano, format='%Y-%m-%d %H:%M:%S'):
    return datetime.datetime.fromtimestamp(nano / 1000000000).strftime(format)


