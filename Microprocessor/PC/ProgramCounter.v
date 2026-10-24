module programcounter(
    input wire clk,
    input wire reset,
    inout    wire[15:0]  bus,
    input wire PCDir,
    input wire PCUOD,
    input wire PCOUT,
    input wire PCIN

);
    wire [15:0] TAddress;
    wire gclk;
    reg [15:0] PC;
    ICG cg(.clk(clk),.en(PCIN),.gclk(gclk));
    always @(posedge gclk , negedge reset) begin
        if(!reset) begin
            PC <= 0;
        end
        else begin
            if(!PCDir) begin
                PC <= bus;
            end
            else if (PCDir && PCUOD) begin
                PC <= PC +1 ;
            end
            else if(PCDir && !PCUOD) begin
                PC <= PC - 1 ;
            end
        end
    end

    assign TAddress = PC;

    bufif1 busbuf [15:0] (bus,TAddress,PCOUT);




endmodule