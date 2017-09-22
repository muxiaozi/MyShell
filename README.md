# MyShell
一个简答的命令解释器（基于Linux开发）

Usage: mydef [FILE]...

Commands
def: def [var]...
	define some variables

set: set <name> <value>
	set value to name

del: del [var]...
	delete variables that given

print:	print [var]...
	print the value of variables

add: add <var1> <var2>
	var1 = var1 + var2

sub: sub <var1> <var2>
	var1 = var1 - var2

mul: mul <var1> <var2>
	var1 = var1 * var2

div: div <var1> <var2>
	var1 = var1 / var2
	Note: var2 can not be 0
