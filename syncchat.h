/* SYNCCHAT.H */

#ifndef _SYNCCHAT_H
#define _SYNCCHAT_H

#define GLOBAL extern	/* turns XSDKVAR.C into a header file */
#include "xsdkvars.c" /* New Addition */

#ifdef __cplusplus
	extern "C" {
#endif

/* SyncChat functions */ 
void get_me(void);
void send_me(void);
int scwhos_online(char listself);
void printall(char *buf);
void print_to_all_nodes_except(char *buf, int i);
char* who_is_on_node(int node);
int registered2(void);
int registered3(void);
int registered4(void);
int registered5(void);
void registered6(void);
void space(int n);
char* full_name(char *s);
char* full_name2(char *s);
char* rollover(char *s);
void print_to_ops(char *buf, char *fname);
void kill_room(int room_num, char* room_dir);
void make_room(int room_num);
void load_rooms_lst(void);
void addto_rooms_lst(char* room);
void removefrom_rooms_lst(void);
void cleanup(void);
void whosin_cur_room(void);
void print_topic(char* str);
void change_topic(void);
void goto_main(int print_boot_msg, int print_header, int del_priv_dir);
void play_games(void);
void create_onfile(void);
void create_gonefile(void);
void delete_gonefile(void);
void delete_onfile(void);
int alone(void);
void free_actions(void);
void free_strings(void);
void get_actions(void);
void get_strings(void);
void delete_topic(void);
void del_prompt(void);
int scusernumber(char *name);
char* scusername(int number);
void edit_e_msgs(void);
void get_e_msgs(void);
void write_e_msgs(void);
void delete_snc_file(void);

/* REGISTRY.C functions */
void registry(void);
void extended_info(void);
void flush_vars(void);

#ifdef __cplusplus
	}
#endif


#endif	/* Don't add anything after this #endif */
