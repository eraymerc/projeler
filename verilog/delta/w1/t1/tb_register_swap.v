
module tb_register_swap;

  // Parameters

  //Ports
  reg  clk;
  reg  rst_n;
  reg wire [7:0] reg1;
  reg wire [7:0] reg2;
  wire [7:0] reg1_out;
  wire [7:0] reg2_out;

  register_swap  register_swap_inst (
    .clk(clk),
    .rst_n(rst_n),
    .reg1(reg1),
    .reg2(reg2),
    .reg1_out(reg1_out),
    .reg2_out(reg2_out)
  );

//always #5  clk = ! clk ;

endmodule