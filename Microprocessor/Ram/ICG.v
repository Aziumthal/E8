module ICG (
    input wire clk,
    input wire en,
    output wire gclk
);
    reg en1;
    initial begin
        en1 = 0;
    end
    always @ (clk , en) begin
        if(!clk)begin
            en1 = en;
        end
    end

    assign gclk = clk & en1;

endmodule

