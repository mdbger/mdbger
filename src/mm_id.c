#include <mm_id.h>

u32 mm_id_node_hcode(mm_id_node* node)
{
	return mm_id_hcode(node->id);
}

u32 mm_id_data_hcode(u8 type, mm_id_t* id)
{
	return mm_id_hcode(*id);
}

int mm_id_node_cmp(mm_id_node* node, u8 type, mm_id_t* id)
{
	int ret = mm_int_cmp(node->type, type);
	if(ret != 0)
		return ret;
	return mm_int_cmp(node->id, *id);
}

static mm_obj_ops s_mm_id_node_ops = {
	(mm_obj_op_hcode)mm_id_node_hcode,
	(mm_obj_op_data_hcode)mm_id_data_hcode,
	(mm_obj_op_cmp)mm_id_node_cmp,
};

const mm_obj_ops* mm_id_node_ops()
{
	return &s_mm_id_node_ops;
}
