sudo rsync -azvv -e ssh ProjectRinzler/ uwesub@192.168.2.20:/home/uwesub/ --exclude-from 'exclude.txt'
