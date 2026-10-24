`timescale 1ns/1ps
module Ramtb();
    reg clk = 0, reset = 0, MARIN = 0, MDRIN = 0, MDRINL = 0,
        MDROUTB = 0, MDROUTR = 0, RAMIN = 0, RAMOUT = 0;
    reg [15:0] busval =16'b0;
    reg benable=0;
    wire [15:0] bus = benable ? busval: 16'bz ; 

    always #5 clk = ~clk;

     RAM_MODULE dut(.bus(bus), .clk(clk), .reset(reset), .MARIN(MARIN), .MDRIN(MDRIN),
                   .MDRINL(MDRINL), .MDROUTB(MDROUTB), .MDROUTR(MDROUTR),
                   .RAMIN(RAMIN), .RAMOUT(RAMOUT));

    initial begin

        $dumpfile("Ram.vcd");
        $dumpvars(0,Ramtb);
        
        reset = 0;
        #11 reset = 1;

        // MAR with 0x1000
        benable = 1;
        busval = 16'h1000;
        @(posedge clk) #1;
        MARIN = 1;
        @(posedge clk) #1;
        MARIN = 0;
        $display("MAR = %h", dut.mar_inst.ToRam);               // 1000

        // MDR with 0x88
        busval = 16'h0088;
        MDRINL = 1; MDRIN = 1;
        @(posedge clk) #1;
        MDRIN = 0; benable = 0;
        $display("MDR = %h", dut.mdr_inst.MDR_Reg);             // 88

        // write MDR into RAM
        MDROUTR = 1; RAMIN = 1;
        @(posedge clk) #1;
        MDROUTR = 0; RAMIN = 0;
        $display("MEM = %h", dut.storage_inst.MEMORY[16'h1000]); // 88

        // clear MDR
        benable = 1; busval = 16'h0000;
        MDRINL = 1; MDRIN = 1;
        @(posedge clk) #1;
        MDRIN = 0; benable = 0;

        // read RAM into MDR
        MDRINL = 0; MDRIN = 1; RAMOUT = 1;
        @(posedge clk) #1;
        MDRIN = 0; RAMOUT = 0;
        $display("MDR = %h", dut.mdr_inst.MDR_Reg);             // 88

        // MDR to the bus
        MDROUTB = 1;
        #1 $display("bus = %h", bus);                           // zz88
        MDROUTB = 0;

        $finish;
end
endmodule