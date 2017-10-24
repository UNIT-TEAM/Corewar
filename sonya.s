.name "Sonya Marmeladova"
	.comment "Man, easy-easy, real tok, think about it!"
	    sti     r1, %:wall, %1
	    sti     r1, %:main, %1
	    sti     r1, %:repeatwall, %1
	    fork    %:main
	    # fork    %:atj1
	    sti     r1,%:staying,%1
	    sti     r1,%:l1,%1
	    sti     r1,%:l2,%1
	    sti     r1,%:l3,%1
	    sti     r1, %:lfork, %7
	    sti     r1, %:lfork, %50

# defdessus:
# 	live	%-42
# 	sti		r10, r11, r13
# 	add		r12, r13, r13
# 	xor		r13, %-255, r14
# 	zjmp	%:zero
# 	ld		%0, r14
# 	zjmp	%:defdessus
# zero:
# 	ld		%0, r13
# 	zjmp	%:defdessus
	    
wall:
	    live    %13
	    st      r2, -10
	    st      r2, -19
	    st      r2, -28
	    st      r2, -37
	    st      r2, -46
	    st      r2, -55
	    st      r2, -64
	    st      r2, -73
	    st      r2, -82
	    st      r2, -91
	    st      r2, -100
	    st      r2, -109
	    st      r2, -118
	    st      r2, -127
	    st      r2, -136
	    st      r2, -145
	    st      r2, -154
	    st      r2, -163
	    st      r2, -172
	    st      r2, -181
	    st      r2, -190
	    st      r2, -199
	    st      r2, -208
	    st      r2, -217
	    st      r2, -226
	    st      r2, -235
	    st      r2, -244
	    st      r2, -253
	    st      r2, -262
	    st      r2, -271
	    st      r2, -280
	    st      r2, -289
	    st      r2, -298
	    st      r2, -307
	    st      r2, -316
	    st      r2, -325
	    ld      %0, r2
	    zjmp    %:wall

main:
	    live    %13
	    fork    %:main
	    live    %13
	    fork    %:repeatwall
	    live    %13
	    fork    %:wall
	    live    %13
	    fork    %:repeatwall

staying:
	            live    %13
l1:
	            live    %13
l2:
	            live    %13
l3:
	            live    %13
	            ld      %0, r2
	            zjmp    %:staying
# atj1:
# 	live	%-42
# 	sti		r1, %:defdessus, %1
# 	ld		%57672959, r10
# 	ld		%-30, r11
# 	ld		%-5, r12
# 	st		r1, 6

repeatwall:
	    live    %13
	    fork    %:wall
lfork:
	    live    %34
	    lfork   %925
	    live    %567
	    lfork   %1941
	    ld      %0, r2
	    zjmp    %:lfork
	