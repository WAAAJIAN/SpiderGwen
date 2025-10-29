import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/spider/GWEN_V2/SpiderGwen/hexapod/hexapod_ros/install/hexapod_ros'
