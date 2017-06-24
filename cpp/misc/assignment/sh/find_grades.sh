
#!/bin/bash

config_dir=$1;
if [ -z $config_dir ]; then
    echo "Please provide config directory";
    echo "usage: ./find_grades.sh config_dir";
    exit 1;
fi

../bin/find_grades $config_dir/config.xml $config_dir/input.xml
