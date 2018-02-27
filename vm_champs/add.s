.name "test add"
.comment "on test tmtc"

		ld %50000000000000, r3
		ld %50000000000000, r2

debut: 	add r3, r2, r3
		zjmp %:debut
