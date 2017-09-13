#include <mm_trace.h>

u32 mm_trace_node_hcode(mm_trace_node* node)
{
	return mm_call_stack_hcode(node->call_stack, node->depth);
}

u32 mm_trace_data_hcode(mm_trace_data* data)
{
	return mm_call_stack_hcode(data->call_stack, )
}

int mm_trace_node_cmp(mm_trace_node* node, u8 type,
	const mm_trace_data* data)
{
	return -1;
}

static mm_obj_ops s_mm_trace_node_ops = {
	(mm_obj_op_hcode)mm_trace_node_hcode,
	(mm_obj_op_data_hcode)mm_trace_data_hcode,
	(mm_obj_op_cmp)mm_trace_node_cmp,
};

const mm_obj_ops* mm_trace_node_ops()
{
	return &s_mm_trace_node_ops;
}
