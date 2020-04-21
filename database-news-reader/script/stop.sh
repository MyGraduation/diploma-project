pid=$( ps -ef | grep 'admin-news-reader' | grep -v grep | awk '{print $2}')
kill -9 $pid
pid=$(lsof -i:8080 | awk '{print $2}')
kill -9 $pid
