#!/bin/bash

# help
./tagmp3 -h > help.out 2>&1
diff help.out test/help.expected
[[ $? -eq 0 ]] || { echo "Help test failed"; exit 1; }

# test setting all tags
cp tiny.mp3 test.mp3

./tagmp3 -t abcdefghijklmnopqrstuvwxyzåäö \
         -a ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ \
         -l abcdefghijklmnopqrstuvwxyzåäö \
         -g abcdefghijklmnopqrstuvwxyzåäö \
         -k 5 \
         -y 1990 \
         -c abcdefghijklmnopqrstuvwxyzåäö \
	test.mp3
./tagmp3 -p test.mp3 > p.out 2>&1
diff p.out test/p.expected
[[ $? -eq 0 ]] || { echo "Set and print tags test failed"; exit 1; }

# test that readonly file can be read (printed)
chmod 444 test.mp3
./tagmp3 -p test.mp3 > readonly.out 2>&1
diff readonly.out test/p.expected
[[ $? -eq 0 ]] || { echo "Printing readonly file failed"; exit 1; }

# cleanup
chmod 644 test.mp3
rm test.mp3

exit 0



