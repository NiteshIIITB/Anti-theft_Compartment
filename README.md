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

## Physical Design

Physical design, in the context of integrated circuit (IC) design, is the process of transforming a logical design description into a physical representation that can be fabricated. This involves translating the high-level abstraction of the design into a detailed representation that includes the placement and routing of physical components on a semiconductor substrate.

### 1. Floorplanning
- Define the overall chip area and allocate space for different functional blocks.
- Consider power grid planning, I/O placement, and chip boundary definition.

### 2. Power Planning
- Establish a power distribution network to ensure all components receive a stable and sufficient power supply.
- Consider power grid topology, voltage drop, and current density.

### 3. Placement
- Positioning of logic cells and other components within the defined chip area.
- Optimize for factors like signal delays, power consumption, and thermal considerations.
- Utilize algorithms to achieve better performance and minimize wirelength.

### 4. Clock Tree Synthesis (CTS)
- Design and optimize the clock distribution network to ensure synchronous operation of the design.
- Minimize skew and jitter in the clock signals.

### 5. Routing
- Establish the physical connections (metal traces) between the placed components.
- Considerations include wirelength, signal integrity, and congestion.
- Use detailed routing algorithms to generate efficient and manufacturable metal layers.

### 6. Physical Verification
- Check the design for adherence to design rules and constraints.
- Includes checks for spacing, width, overlap, and other manufacturing constraints.
- Ensure that the design meets the foundry's specifications.

### 7. Extraction
- Model the parasitic effects of interconnects (resistance, capacitance, etc.).
- Extraction tools generate a more accurate representation of the circuit's behavior.

### 8. Timing Analysis
- Evaluate and optimize the timing characteristics of the design.
- Check for setup and hold times, clock-to-q delays, and overall performance.
- Iterative optimization may be required to meet timing constraints.

### 9. Signal Integrity Analysis
- Analyze and address issues related to signal quality, such as crosstalk and noise.
- Ensure that signals reach their destinations with minimal distortion.

### 10. Physical Testing and Debugging
- Simulate and test the physical design to ensure functionality.
- Debug and refine the design if necessary.

## Synthesis

Synthesis in EDA tools is primarly of two steps.
- RTL is converted into a generic gate level netlist.
- Technology mapping is done and generic level netlist is converted to standard netlist.
  
To synthesize the code run the following command

```
run_synthesis
```

![Screenshot from 2023-11-16 14-59-05](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/81449275-0579-4c17-8556-31cd7a816df9)


#### Results after Synthesis
![Screenshot from 2023-11-16 14-43-16](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/251df023-375e-4520-94a8-aac9e513534c)


## Floorplan

In the process of ASIC design, floorplanning is crucial for planning the silicon area and creating a robust Power Distribution Network (PDN). The floorplan defines the physical layout of the chip, including core utilization, aspect ratio, margins, and pin configurations. Additionally, it involves strategies such as creating power rings, power straps, macro placement, and blockages to ensure a legalized GDS file.

### Floorplan Environment Variables:

- **FP_CORE_UTIL**: Floorplan core utilization, specifying the percentage of the chip's core area that will be utilized.

- **FP_ASPECT_RATIO**: Floorplan aspect ratio, defining the ratio of the chip's width to its height.

- **FP_CORE_MARGIN**: Core to die margin area, specifying the margin between the core area and the chip boundary.

- **FP_IO_MODE**: Defines pin configurations.
  - 1: Equidistant pin configuration.
  - 0: Non-equidistant pin configuration.

- **FP_CORE_VMETAL**: Vertical metal layer for the core.

- **FP_CORE_HMETAL**: Horizontal metal layer for the core.

Note: Metal layer values are typically one more than specified in the file.

### Power Planning Strategies:

- **Power Rings**: Rings around the edges of the chip connected to the pads to distribute power uniformly.

- **Power Straps**: Higher metal layers used to bring power to the middle of the chip, reducing IR drop and electro-migration problems.

#### Floorplan Command:

To run the floorplan using these environment variables and switches, use the following command:

```
run_floorplan
```

![Screenshot from 2023-11-16 15-00-13](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/4eec3176-b103-4d5a-a8ba-0ca30cfd239e)


- Post the floorplan run, a .def file will have been created within the results/floorplan directory. We may review floorplan files by checking the floorplan.tcl.
- To view the floorplan: Magic is invoked after moving to the results/floorplan directory,then use the floowing command:

```
magic -T /home/nitesh/Desktop/sky130A.tech lef read /home/nitesh/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

```

![floorplan_magic](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/52491279-4a20-405f-874d-5f21d08209a3)


#### Core area(post floorplan)
![Screenshot from 2023-11-16 15-09-48](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/995ac3dc-697b-4336-a317-b7db15bde205)

#### Die area(post floorplan)
![Screenshot from 2023-11-16 15-11-34](https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/b99cea0d-f55a-4c9d-83de-2c0ea9a38fe6)


# Placement Stage in OpenLANE

The placement stage in OpenLANE involves placing standard cells on floorplan rows, aligned with the sites defined in the technology LEF file. The placement is performed in two steps: Global Placement and Detailed Placement.

- Global Placement: Global placement attempts to find an optimal position for all cells, even if they may initially overlap and not align with the rows defined in the floorplan. The optimization during global placement focuses on reducing half-parameter wire length.

- Detailed Placement:  Detailed placement takes the result of global placement and legalizes the positions of cells, adhering to the preferences established during global placement. This step ensures that the final placement is both optimal and adheres to specific design rules.

#### Running Placement:

To run the placement process, use the following command:

```
run_placement
```
<div align="center">
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/bc90be8c-0676-4809-8981-a25cdb87d291">
</div>

- Post placement: the design can be viewed on magic within results/placement directory. Run the follwing command in that directory:

  ```
  magic -T /home/nitesh/Desktop/sky130A.tech lef read /home/nitesh/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

  ```

  <div align="center">
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/7241bc4a-1b29-4324-8b1a-48b3fbfb3cde">
</div>

## Clock Tree Synthesis (CTS) in OpenLANE

Clock Tree Synthesis (CTS) is a crucial step in the OpenLANE ASIC flow, designed to create an optimized clock distribution network for delivering the clock to all sequential elements on the chip. The primary goal is to achieve minimal clock skew across the entire chip, and H-trees are commonly employed as a network topology to fulfill this objective.

#### Purpose of CTS:

The main purposes of building a clock tree are:
- Enabling the clock input to reach every sequential element on the chip.
- Ensuring zero clock skew, minimizing the time delay between different parts of the clock network.

#### H-Tree Methodology:

H-trees are a common methodology followed in CTS due to their effectiveness in minimizing skew. The H-tree structure involves a hierarchical distribution of the clock signal, branching out from a central point to cover different regions of the chip.

#### Running CTS:

To perform Clock Tree Synthesis in OpenLANE, use the following command:

```
run_cts
```
### Timing reports
<div align="center">
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/50a9f6f4-b561-4cc3-990c-0a3bc18dc2a7">
</div>

### Area Report
<div align="center">
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/9cf23d8c-1391-4e5e-a2df-99fcb5ca1b88">
</div>

### Power Report
<div align="center">
	<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/e60771fb-4833-4294-9548-05760dfa93c2">
</div>

## Routing in OpenLANE

Routing in OpenLANE involves implementing the interconnect system between standard cells using the remaining available metal layers after Clock Tree Synthesis (CTS) and Power Distribution Network (PDN) generation. The routing is performed on routing grids to ensure minimal Design Rule Check (DRC) errors.

OpenLANE utilizes the TritonRoute tool for routing, and the process consists of two stages:

#### Global Routing:
Global routing divides the routing region into rectangular grids, represented as coarse 3D routes using the Fastroute tool.

#### Detailed Routing:
Detailed routing uses finer grids and routing guides to implement the physical wiring. TritonRoute, another tool in the OpenLANE flow, is responsible for this stage.

#### Features of TritonRoute:
- Honoring pre-processed route guides.
- Assumes that each net satisfies inter-guide connectivity.
- Utilizes a Mixed-Integer Linear Programming (MILP) based panel routing scheme.
- Employs an intra-layer parallel and inter-layer sequential routing framework.

#### Running Routing in OpenLANE:

To run the routing process, use the following command:

```
 run_routing
```

- Layout in magic tool post routing: the design can be viewed on magic within results/routing directory. Run the follwing command in that directory:

  ```
  magic -T /home/nitesh/Desktop/sky130A.tech lef read /home/nitesh/OpenLane/designs/processor_project/runs/RUN_2023.11.13_10.50.18/tmp/merged.nom.lef def read wrapper.def &

  ```
 ### Layout after Routing 
<div align="center">  
	
<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/f658634c-b3d1-48d1-9d32-054cd4b8ed4f">
<img src= "https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/0dbe3c4a-5558-48f9-bb56-d8ab5cc96c20">

</div>

### Post Routing Timing report
<div align="center">
<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/34735f23-33de-41ac-a068-7216b47759db">
</div>



### Post Routing Area report
<div align="center">
<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/ce3a4b9b-d387-44e9-af7b-57493b6a124e">
</div>


### Post Routing Power report
<div align="center">
<img src="https://github.com/NiteshVLSI/Anti-theft_Compartment/assets/140998787/72651832-c62e-47e0-894e-d36aa8088b14">
</div>


## Performance calculation
- Clock period : 100ns
- setup slack  : 28.33ns

```
                              1
Max Performance =  ------------------------    = 13.95 MHz
                     clock period - slack(setup)
```

## Summary of Commands

```
cd Desktop/OpenLane/ 

./flow.tcl -interactive
package require openlane 0.9
prep -design project
run_synthesis
run_floorplan
run_placement
run_cts
gen_pdn
run_routing
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check


```
## Word of Thanks

I would like to sincerely thank Mr. Kunal Gosh, Founder of VSD (VLSI System Design), for his invaluable assistance and guidance, which played a pivotal role in ensuring the smooth completion of this project flow.


## References

- [OpenSTA GitHub Repository](https://github.com/The-OpenROAD-Project/OpenSTA.git)
- [kunalg123 GitHub Profile](https://github.com/kunalg123)
- [VSDIAT Official Website](https://www.vsdiat.com)
- [RISCV-GNU GitHub Repository by Saketh Gajawada](https://github.com/SakethGajawada/RISCV-GNU)
- [Mayank Kabra, Founder, Chipcron Pvt. Ltd.](https://www.tofler.in/mayank-kabra/director/10086358)

