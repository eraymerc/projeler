module register_swap (
    input wire clk,       // Clock input
    input wire rst_n,     // Asynchronous active-low reset input
    input wire [7:0] reg1, // First register input
    input wire [7:0] reg2, // Second register input
    output reg [7:0] reg1_out, // First register output
    output reg [7:0] reg2_out // Second register output
);

// Asynchronous reset logic
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        reg1_out <= 8'h00; // Reset reg1_out to 0
        reg2_out <= 8'h00; // Reset reg2_out to 0
    end else begin
        // Swap logic
        reg1_out <= reg2; // Assign reg2 to reg1_out
        reg2_out <= reg1; // Assign reg1 to reg2_out
    end
end

endmodule
