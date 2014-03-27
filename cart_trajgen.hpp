/*
 * cart_trajgen microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

/* includes types and type metadata */

ubx_type_t types[] = {
	{ NULL },
};

/* block meta information */
char cart_trajgen_meta[] =
	" { doc='',"
	"   license='',"
	"   real-time=true,"
	"}";

/* declaration of block configuration */
ubx_config_t cart_trajgen_config[] = {
	{ .name="max_vel", .type_name = "struct kdl_twist", .doc="maximum velocity" },
	{ .name="max_acc", .type_name = "struct kdl_twist", .doc="maximum acceleration" },
	{ NULL },
};

/* declaration port block ports */
ubx_port_t cart_trajgen_ports[] = {
	{ .name="des_pos", .in_type_name="struct kdl_frame", .in_data_len=1, .doc="desired target position"  },
	{ .name="msr_pos", .in_type_name="struct kdl_frame", .in_data_len=1, .doc="current measured position"  },
	{ .name="des_dur", .in_type_name="double", .in_data_len=1, .doc="desired duration of trajectory [s] "  },
	{ .name="cmd_pos", .out_type_name="struct kdl_frame", .out_data_len=1, .doc="next position increment"  },
	{ .name="cmd_vel", .out_type_name="struct kdl_twist", .out_data_len=1, .doc="next velocity increment"  },
	{ .name="reached", .out_type_name="int", .out_data_len=1, .doc="outputs 1 if the trajectory has been output entirely"  },
	{ .name="move_dur", .out_type_name="double", .out_data_len=1, .doc="time since last move to command [s]"  },
	{ NULL },
};

/* declare a struct port_cache */
struct cart_trajgen_port_cache {
	ubx_port_t* des_pos;
	ubx_port_t* msr_pos;
	ubx_port_t* des_dur;
	ubx_port_t* cmd_pos;
	ubx_port_t* cmd_vel;
	ubx_port_t* reached;
	ubx_port_t* move_dur;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct cart_trajgen_port_cache *pc)
{
	pc->des_pos = ubx_port_get(b, "des_pos");
	pc->msr_pos = ubx_port_get(b, "msr_pos");
	pc->des_dur = ubx_port_get(b, "des_dur");
	pc->cmd_pos = ubx_port_get(b, "cmd_pos");
	pc->cmd_vel = ubx_port_get(b, "cmd_vel");
	pc->reached = ubx_port_get(b, "reached");
	pc->move_dur = ubx_port_get(b, "move_dur");
}


/* for each port type, declare convenience functions to read/write from ports */
def_read_fun(read_des_pos, struct kdl_frame)
def_read_fun(read_msr_pos, struct kdl_frame)
def_read_fun(read_des_dur, double)
def_write_fun(write_cmd_pos, struct kdl_frame)
def_write_fun(write_cmd_vel, struct kdl_twist)
def_write_fun(write_reached, int)
def_write_fun(write_move_dur, double)

/* block operation forward declarations */
int cart_trajgen_init(ubx_block_t *b);
int cart_trajgen_start(ubx_block_t *b);
void cart_trajgen_stop(ubx_block_t *b);
void cart_trajgen_cleanup(ubx_block_t *b);
void cart_trajgen_step(ubx_block_t *b);


/* put everything together */
ubx_block_t cart_trajgen_block = {
	.name = "cart_trajgen",
	.type = BLOCK_TYPE_COMPUTATION,
	.meta_data = cart_trajgen_meta,
	.configs = cart_trajgen_config,
	.ports = cart_trajgen_ports,

	/* ops */
	.init = cart_trajgen_init,
	.start = cart_trajgen_start,
	.stop = cart_trajgen_stop,
	.cleanup = cart_trajgen_cleanup,
	.step = cart_trajgen_step,
};


/* cart_trajgen module init and cleanup functions */
int cart_trajgen_mod_init(ubx_node_info_t* ni)
{
	DBG(" ");
	int ret = -1;
	ubx_type_t *tptr;

	for(tptr=types; tptr->name!=NULL; tptr++) {
		if(ubx_type_register(ni, tptr) != 0) {
			goto out;
		}
	}

	if(ubx_block_register(ni, &cart_trajgen_block) != 0)
		goto out;

	ret=0;
out:
	return ret;
}

void cart_trajgen_mod_cleanup(ubx_node_info_t *ni)
{
	DBG(" ");
	const ubx_type_t *tptr;

	for(tptr=types; tptr->name!=NULL; tptr++)
		ubx_type_unregister(ni, tptr->name);

	ubx_block_unregister(ni, "cart_trajgen");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(cart_trajgen_mod_init)
UBX_MODULE_CLEANUP(cart_trajgen_mod_cleanup)
