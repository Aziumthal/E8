`timescale 1ns/1ps
module ProgramCounter_tb();
    reg clk =0,reset = 0,PCDir = 0,PCUOD= 0,PCOUT = 0,PCIN = 0,busen = 0;
    reg [15:0] busval =16'b0;
    wire [15:0] bus;

    assign bus = busen ? busval: 16'bz;

    programcounter pc_test (
        .clk(clk),
        .reset(reset),
        .bus(bus),
        .PCDir(PCDir),
        .PCUOD(PCUOD),
        .PCOUT(PCOUT),
        .PCIN(PCIN)
    );

    always #5 clk = ~clk;

    initial begin
        $dumpfile("PC.vcd");
        $dumpvars(0,ProgramCounter_tb);

        reset = 0;
        #11 reset = 1;
        busen = 1; busval = 16'h0005;
        PCDir = 0; PCIN = 1;
        @(posedge clk); #1;
        $display("PC : %h", pc_test.PC);    // 0005
        busen = 0;
        PCDir = 1; PCUOD = 1;
        @(posedge clk); #1;
        $display("PC : %h", pc_test.PC);    // 0006
        @(posedge clk); #1;
        $display("PC : %h", pc_test.PC);    // 0007
        PCUOD = 0;
        @(posedge clk); #1;
        $display("PC : %h", pc_test.PC);    // 0006
        PCIN = 0; PCOUT = 1;
        #1 $display("bus : %h", bus);       // 0006

        $finish;
    end
endmodule