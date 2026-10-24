module MAR(
    input wire [15:0] bus,
    input wire clk,
    input wire MARIN,
    input wire reset,
    output reg [15:0] ToRam
);
    wire gclk;
    ICG cg(.clk(clk),.en(MARIN),.gclk(gclk));

    always @(posedge gclk, negedge reset) begin
        if(!reset) begin
            ToRam <= 16'b0;
        end
        else begin
            ToRam <= bus;
        end
    end

endmodule


module MDR(
    inout wire [15:0] bus,
    inout wire [7:0] ram,
    input wire clk,
    input wire MDRIN,
    input wire reset,
    input wire MDRINL,
    input wire MDROUTB,
    input wire MDROUTR
);
    wire gclk;
    wire [7:0] MDRI;
    reg [7:0] MDR_Reg;
    wire [7:0] Tram,Tbus;

    ICG cg (.clk(clk), .en(MDRIN), .gclk(gclk));

    assign MDRI = MDRINL ? bus[7:0] : ram;

    always @(posedge gclk or negedge reset) begin
        if (!reset)
            MDR_Reg <= 8'b0;
        else
            MDR_Reg <= MDRI;
    end

    assign Tbus = MDR_Reg;  //Apparently inout cannot be in always block so I use ut like this
    assign Tram = MDR_Reg;  // Not using a MUX to select output since the buffer controls where the data goes anwyays

    bufif1 busbuf [7:0] (bus[7:0],Tbus,MDROUTB);
    bufif1 rambuf [7:0] (ram,Tram,MDROUTR);



endmodule

module Storage(
    input RAMIN,
    input RAMOUT,
    input [15:0] address ,
    inout [7:0] data,
    input clk
);
    reg [7:0] MEMORY [65535:0];
    wire [7:0] tdata;
   
    assign tdata = MEMORY[address];
    bufif1 bufram [7:0] (data,tdata,RAMOUT);

    always @(posedge clk) begin
        if(RAMIN)begin
            MEMORY[address] <= data;
        end
    end
endmodule

module RAM_MODULE(
    inout  wire [15:0] bus,
    input  wire clk,
    input  wire reset,
    input  wire MARIN,
    input  wire MDRIN,
    input  wire MDRINL,
    input  wire MDROUTB,
    input  wire MDROUTR,
    input wire RAMIN,
    input wire RAMOUT
); 

    wire [15:0] ToRam;
    wire [7:0] ram;
    

    MAR mar_inst (
        .bus(bus),
        .clk(clk),
        .MARIN(MARIN),
        .reset(reset),
        .ToRam(ToRam)
    );

    MDR mdr_inst (
        .bus(bus),
        .ram(ram),
        .clk(clk),
        .MDRIN(MDRIN),
        .reset(reset),
        .MDRINL(MDRINL),
        .MDROUTB(MDROUTB),
        .MDROUTR(MDROUTR)
    );


    Storage storage_inst (
        .RAMIN(RAMIN),
        .clk(clk),
        .RAMOUT(RAMOUT),
        .data(ram),
        .address(ToRam)
    );

endmodule


