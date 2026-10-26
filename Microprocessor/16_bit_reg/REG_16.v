module Register16 #(
    parameter [15:0] RESET_VAL = 16'h0000
)(
    input wire clk,
    input wire reset,
    inout wire[15:0]  bus,
    input wire RegDir,
    input wire RegUOD,
    input wire RegOUT,
    input wire RegIN
);
    wire [15:0] TAddress;
    wire gclk;
    reg [15:0] Reg;
    ICG cg(.clk(clk),.en(RegIN),.gclk(gclk));
    always @(posedge gclk , negedge reset) begin
        if(!reset) begin
            Reg <= RESET_VAL;
        end
        else begin
            if(!RegDir) begin
                Reg <= bus;
            end
            else if (RegDir && RegUOD) begin
                Reg <= Reg +1 ;
            end
            else if(RegDir && !RegUOD) begin
                Reg <= Reg - 1 ;
            end
        end
    end

    assign TAddress = Reg;

    bufif1 busbuf [15:0] (bus,TAddress,RegOUT);


endmodule