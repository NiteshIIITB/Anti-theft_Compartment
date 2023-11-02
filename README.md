# Anti-theft_Compartment

### Project Overview

The Anti-Theft Compartment project is a comprehensive security solution designed to safeguard valuable belongings from unauthorized access. This project combines hardware and software components, featuring a digital light sensor to detect intrusion and trigger an alarm. Beyond security, it presents an opportunity to explore the details of RISC-V ISA for ASIC implementation. 



### Key Features

- **Light Sensor-Based Intrusion Detection:** The project relies on a digital light sensor to detect unauthorized access, promptly triggering an alarm when the compartment is opened.

- **Alarm Activation:** An alarm system is integrated to provide immediate notification upon unauthorized access.

- **Customizable Hardware and Software:** The project offers flexibility, allowing users to customize both hardware components and software logic to suit their specific requirements.

- **Well-Documented Code:** Clear and comprehensive documentation accompanies the code, making implementation straightforward and user-friendly.

- **Room for Enhancements:** The project is designed with room for further enhancements and integrations, enabling users to expand its capabilities as needed.

<h2>Block Diagram</h2>
<div>
	<img src="https://github.com/NiteshIIITB/Anti-theft_Compartment/assets/140998787/3d857054-9e97-4d45-b923-02434353f34d">

</div>


<h2>C Code</h2>

```

int main()  {
    int light_sensor;
    int buzzer;
    int buff;
  //  int input = 0xFFFFFFF0;
    
  while(1)   {
        // Read sensor data into x30
        asm (
            
            "andi %0, x30, 1"
            : "=r"(light_sensor)
             
        );

        if (light_sensor) {
            // If light sensor output is 1, turn on buzzer
            buff = 0xFFFFFFFD;
            asm (
                "and x30, x30, %1\n\t"     // Clear the 2nd bit from lsb
                "ori x30, x30, 2\n\t" // Check if 2nd bit is set
                "andi %0, x30, 2"
                : "=r"(buzzer)
                : "r"(buff)
            );
        } else {
            // If light sensor output is 0, turn off the buzzer
            buff = 0xFFFFFFFD;
            asm (
                "and x30, x30, %1\n\t"     // Clear the 2nd bit from lsb
                "and %0,  x30, 2"
                : "=r"(buzzer)
                : "r"(buff)
              
            );
        }
         return 0;
    }
    
   
   
}



```



<h2>Assembly Code</h2>



```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fe010113          	addi	sp,sp,-32
   10058:	00812e23          	sw	s0,28(sp)
   1005c:	02010413          	addi	s0,sp,32
   10060:	001f7793          	andi	a5,t5,1
   10064:	fef42623          	sw	a5,-20(s0)
   10068:	fec42783          	lw	a5,-20(s0)
   1006c:	02078263          	beqz	a5,10090 <main+0x3c>
   10070:	ffd00793          	li	a5,-3
   10074:	fef42423          	sw	a5,-24(s0)
   10078:	fe842783          	lw	a5,-24(s0)
   1007c:	00ff7f33          	and	t5,t5,a5
   10080:	002f6f13          	ori	t5,t5,2
   10084:	002f7793          	andi	a5,t5,2
   10088:	fef42223          	sw	a5,-28(s0)
   1008c:	01c0006f          	j	100a8 <main+0x54>
   10090:	ffd00793          	li	a5,-3
   10094:	fef42423          	sw	a5,-24(s0)
   10098:	fe842783          	lw	a5,-24(s0)
   1009c:	00ff7f33          	and	t5,t5,a5
   100a0:	002f7793          	andi	a5,t5,2
   100a4:	fef42223          	sw	a5,-28(s0)
   100a8:	00000793          	li	a5,0
   100ac:	00078513          	mv	a0,a5
   100b0:	01c12403          	lw	s0,28(sp)
   100b4:	02010113          	addi	sp,sp,32
   100b8:	00008067          	ret

```

<h2>Instructions</h2>

```
Number of different instructions: 11
List of unique instructions:
lw
mv
li
ori
j
and
beqz
ret
andi
addi
sw


```

## Spike Simulation
### Modified C code

In this code I have manually changed the value of input (which will be controlled externally in ic) and observed the corresponding values of output through spike.

```
#include<stdio.h>
#include<stdlib.h>

int main()  {
    int light_sensor;
    int buzzer;
    int buff;
    int input = 0xFFFFFFF1;
    
     {
        // Read sensor data into x30
        asm (
            "and x30, %1, %2\n\t"
            "andi %0, x30, 1"
            : "=r"(light_sensor)
            : "r"(input), "r"(0xFFFFFFFF)
        );

        if (light_sensor) {
            // If light sensor output is 1, turn on buzzer
            buff = 0xFFFFFFFD;
            asm (
                "and x30, x30, %1\n\t"     // Clear the 2nd bit from lsb
                "ori x30, x30, 2\n\t" // Check if 2nd bit is set
                "andi %0, x30, 2"
                : "=r"(buzzer)
                : "r"(buff)
            );
        } else {
            // If light sensor output is 0, turn off the buzzer
            buff = 0xFFFFFFFD;
            asm (
                "and x30, x30, %1\n\t"     // Clear the 2nd bit from lsb
                "and %0,  x30, 2"
                : "=r"(buzzer)
                : "r"(buff)
              
            );
        }
    }
    
    if (buzzer==2){printf("buzzer is on, Value of buzzer is %d \n",buzzer);}
    else{printf("buzzer is off, Value of buzzer is %d \n",buzzer);}
    return 0;
}


```

### Spike output
When input is 1 to temp_sensor.
<div>
	<img src= https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/2e9871ac-6e0a-4698-aaff-55c275c66bfe>

</div>

<br>
When input is 1 to temp_sensor.
<div>
	<img src= "https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/e82aa641-7bac-478f-a171-662f50569bf3">

</div>

## Functional Verification
<div>
	<img src= https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/ee138bb5-2e5d-418b-830a-7b65128f3ee4 >
	

</div>

<br>
<div>
	<img src = "https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/25d259a8-0ed3-4f7a-8257-2fe51a1390d5">
</div>


<br>
<p>
	<b>001f7793:</b> This line is the andi instruction. It performs a bitwise AND operation on the values of t5 and 1, storing the result in a5.At this instruction input is being read.
	<br>
	<b>02078263:</b> This line is the beqz instruction. It branches to the memory address 10090 if the value in a5 is zero.
	<br>
	<b>002f6f13:</b> This line is the ori instruction. It performs a bitwise OR operation on the values of t5 and 2, storing the result in t5.At this instruction output is set to 1.
	<br>
        <b>000f0793:</b> This line is the mv instruction. It moves the value of t5 to a5.
	<br>
	<b>fef42023:</b> This line is the sw instruction. It stores the value of a5 in the memory at an offset of -32 from s0.

        
</p>
</div>

## GLS

GLS typically stands for "Gate Level Simulation." It is a method used in digital design and verification to simulate the behavior of the synthesized netlist or gate-level representation of a design. This simulation verifies that the logical functionality of the gate-level design matches the intended behavior described in the RTL (Register Transfer Level) design.
Below are the commands used for Netlist generation(Logic Synthesis)

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor_test.v

```

command to run gls simulation

```

iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v

```


<b>Highlighted the wrapper module after netlist created</b>
<div>
	<img src= "https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/0c075205-0bcb-473a-a3cb-e173381875f9">
</div>

<b>GLS SImulation results</b>
<div>
	<img src= "https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/543f6e48-8813-436e-9954-ab81501f26a5">
</div>

<div>
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/f48fef88-71dd-4c47-83bf-5c9e372e0734">
</div>

## Word of Thanks

I would like to sincerely thank Mr. Kunal Gosh, Founder of VSD (VLSI System Design), for his invaluable assistance and guidance, which played a pivotal role in ensuring the smooth completion of this project flow.


## References

- [OpenSTA GitHub Repository](https://github.com/The-OpenROAD-Project/OpenSTA.git)
- [kunalg123 GitHub Profile](https://github.com/kunalg123)
- [VSDIAT Official Website](https://www.vsdiat.com)
- [RISCV-GNU GitHub Repository by Saketh Gajawada](https://github.com/SakethGajawada/RISCV-GNU)
- [Mayank Kabra, Founder, Chipcron Pvt. Ltd.](https://www.tofler.in/mayank-kabra/director/10086358)

