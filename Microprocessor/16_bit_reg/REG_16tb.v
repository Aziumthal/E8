`timescale 1ns/1ps
module Register16_tb();
    reg clk =0,reset = 0,RegDir = 0,RegUOD= 0,RegOUT = 0,RegIN = 0,busen = 0;
    reg [15:0] busval =16'b0;
    wire [15:0] bus;

    assign bus = busen ? busval: 16'bz;

    Register16 #(.RESET_VAL(16'h0000)) reg_test (
        .clk(clk),
        .reset(reset),
        .bus(bus),
        .RegDir(RegDir),
        .RegUOD(RegUOD),
        .RegOUT(RegOUT),
        .RegIN(RegIN)
    );

    always #5 clk = ~clk;

    initial begin
        $dumpfile("Reg.vcd");
        $dumpvars(0,Register16_tb);

        reset = 0;
        #11 reset = 1;
        busen = 1; busval = 16'h0005;
        RegDir = 0; RegIN = 1;
        @(posedge clk); #1;
        $display("Reg : %h", reg_test.Reg);    // 0005
        busen = 0;
        RegDir = 1; RegUOD = 1;
        @(posedge clk); #1;
        $display("Reg : %h", reg_test.Reg);    // 0006
        @(posedge clk); #1;
        $display("Reg : %h", reg_test.Reg);    // 0007
        RegUOD = 0;
        @(posedge clk); #1;
        $display("Reg : %h", reg_test.Reg);    // 0006
        RegIN = 0; RegOUT = 1;
        #1 $display("bus : %h", bus);          // 0006

        $finish;
    end
endmodule