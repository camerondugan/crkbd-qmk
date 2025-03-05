all: left right
	ls

right: 
	qmk flash -bl avrdude-split-right

left: 
	qmk flash -bl avrdude-split-left
