#==========================================================================
#   Copyright (C) 2020 wang. All rights reserved.
#   
#   Authors:    wanglongfei(395592722@qq.com)
#   Date:       2020/04/12 17:38:20
#   Description:
#
#==========================================================================

pid=$( ps -ef | grep 'spider-news-reader' | grep -v grep | awk '{print $2}')
kill -9 $pid

