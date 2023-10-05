# Anti-theft_Compartment


<h2>C Code</h2>

```

int main()  {

    
    int light_sensor;
    int buzzer;
    int buff;
    
    
        while(1) {
        // Read sensor data into x30
	asm (
            "and %0, x30, 1"
            : "=r"(light_sensor)
        );

       
        

        
        if (light_sensor) {
            // If light sensor output is 1 turn on buzzer
            buff =0xFFFFFFFD;
            asm(
            "and x30,x30, %0\n\t"     // Making 2nd bit from lsb0
            "or %1, x30,2"                 // output at 2nd bit that turn on buzzer
            :"=r"(buff)
            :"r"(buzzer)
        );
        } 
        else {
            // If light sensor output is 0 turn off the buzzer
            buff =0xFFFFFFFD;
            asm(
            "and x30,x30, %0\n\t"     
            "or %1, x30,0"            //Making 2nd bit from lsb(output) as 0
            :"=r"(buff)
            :"r"(buzzer)
        );
        }
    return 0;
}

}



```

<h2>Assembly Code</h2>

```

sample:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	fe010113          	add	sp,sp,-32
   4:	00812e23          	sw	s0,28(sp)
   8:	02010413          	add	s0,sp,32
   c:	001f7793          	and	a5,t5,1
  10:	fef42623          	sw	a5,-20(s0)
  14:	fec42783          	lw	a5,-20(s0)
  18:	02078063          	beqz	a5,38 <.L2>
  1c:	ffd00793          	li	a5,-3
  20:	fef42423          	sw	a5,-24(s0)
  24:	fe442783          	lw	a5,-28(s0)
  28:	00ff7f33          	and	t5,t5,a5
  2c:	002f6793          	or	a5,t5,2
  30:	fef42423          	sw	a5,-24(s0)
  34:	01c0006f          	j	50 <.L3>

00000038 <.L2>:
  38:	ffd00793          	li	a5,-3
  3c:	fef42423          	sw	a5,-24(s0)
  40:	fe442783          	lw	a5,-28(s0)
  44:	00ff7f33          	and	t5,t5,a5
  48:	000f6793          	or	a5,t5,0
  4c:	fef42423          	sw	a5,-24(s0)

00000050 <.L3>:
  50:	00000793          	li	a5,0
  54:	00078513          	mv	a0,a5
  58:	01c12403          	lw	s0,28(sp)
  5c:	02010113          	add	sp,sp,32
  60:	00008067          	ret

```
