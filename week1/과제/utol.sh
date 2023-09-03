echo -e 'Working directory' #/sogang/under/cse20131251/shell 
read dirname #directory 이름을 입력을 저장

if [ ! -d $dirname ]
then
	echo "cannot change directory!"
elif [ -n "$dirname" ]  
then
	for dir in $(ls $dirname)
	do
		newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
		mv $dir $newname
	done
else
	for dir in *
	do
		newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
		mv $dir $newname
	done
fi
