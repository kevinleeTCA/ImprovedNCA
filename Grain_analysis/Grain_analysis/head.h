#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <map>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <io.h>
#include <direct.h>
#include <set>
#include <vector>
using namespace std;

using std::cin;
using std::cout;
using std::cerr;
using std::string;
using std::endl;
using std::ends;
using std::istream;
using std::ostream;

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned char u8;


//Grain v1 full version

typedef struct
{
	u32 LFSR[80];
	u32 NFSR[80];
	const u8* p_key;
	u32 keysize;
	u32 ivsize;

} ECRYPT_ctx;


#ifndef GRAIN_H
#define INITCLOCKS 160
#define N(i) (ctx->NFSR[80-i])
#define L(i) (ctx->LFSR[80-i])
#define X0 (ctx->LFSR[3])
#define X1 (ctx->LFSR[25])
#define X2 (ctx->LFSR[46])
#define X3 (ctx->LFSR[64])
#define X4 (ctx->NFSR[63])
static const u8 NFTable[1024]= {0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,0,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,1,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,
								1,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,1,1,1,1,0,1,1,1,1,
								0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,1,1,1,
								1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,
								0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,
								1,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1,1,1,1,
								0,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,0,1,1,0,
								1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1,0,1,0,0,0,1,1,0,
								1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,0,1,1,0,0,
								0,1,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,1,1,0,1,1,0,0,
								1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1,1,1,0,0,1,
								0,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,0,1,1,0,
								1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,0,1,1,0,0,
								1,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,0,0,0,1,1};


								 
static const u8 boolTable[32] = {0,0,1,1,0,0,1,0,0,1,1,0,1,1,0,1,1,1,0,0,1,0,1,1,0,1,1,0,0,1,0,0};
#endif

/* Mandatory functions */

/*
 * Key and message independent initialization. This function will be
 * called once when the program starts (e.g., to build expanded S-box
 * tables).
 */
void ECRYPT_init();

/*
 * Key setup. It is the user's responsibility to select the values of
 * keysize and ivsize from the set of supported values specified
 * above.
 */
void ECRYPT_keysetup(
  ECRYPT_ctx* ctx, 
  const u8* key, 
  u32 keysize,                /* Key size in bits. */ 
  u32 ivsize);                /* IV size in bits. */ 

/*
 * IV setup. After having called ECRYPT_keysetup(), the user is
 * allowed to call ECRYPT_ivsetup() different times in order to
 * encrypt/decrypt different messages with the same key but different
 * IV's.
 */
void ECRYPT_ivsetup(
  ECRYPT_ctx* ctx, 
  const u8* iv);



/*
 * Encryption/decryption of arbitrary length messages.
 *
 * For efficiency reasons, the API provides two types of
 * encrypt/decrypt functions. The ECRYPT_encrypt_bytes() function
 * (declared here) encrypts byte strings of arbitrary length, while
 * the ECRYPT_encrypt_blocks() function (defined later) only accepts
 * lengths which are multiples of ECRYPT_BLOCKLENGTH.
 * 
 * The user is allowed to make multiple calls to
 * ECRYPT_encrypt_blocks() to incrementally encrypt a long message,
 * but he is NOT allowed to make additional encryption calls once he
 * has called ECRYPT_encrypt_bytes() (unless he starts a new message
 * of course). For example, this sequence of calls is acceptable:
 *
 * ECRYPT_keysetup();
 *
 * ECRYPT_ivsetup();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_bytes();
 *
 * ECRYPT_ivsetup();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_blocks();
 *
 * ECRYPT_ivsetup();
 * ECRYPT_encrypt_bytes();
 * 
 * The following sequence is not:
 *
 * ECRYPT_keysetup();
 * ECRYPT_ivsetup();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_bytes();
 * ECRYPT_encrypt_blocks();
 */

void ECRYPT_encrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* plaintext, 
  u8* ciphertext, 
  u32 msglen);                /* Message length in bytes. */ 

void ECRYPT_decrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* ciphertext, 
  u8* plaintext, 
  u32 msglen);                /* Message length in bytes. */ 

/* Optional features */

/* 
 * For testing purposes it can sometimes be useful to have a function
 * which immediately generates keystream without having to provide it
 * with a zero plaintext. If your cipher cannot provide this function
 * (e.g., because it is not strictly a synchronous cipher), please
 * reset the ECRYPT_GENERATES_KEYSTREAM flag.
 */

#define ECRYPT_GENERATES_KEYSTREAM_BIT
#ifdef ECRYPT_GENERATES_KEYSTREAM_BIT
	u8 ENCRYPT_grain_keystream(
		ECRYPT_ctx* ctx);
#endif

#define ECRYPT_GENERATES_KEYSTREAM_E_KSDC
#ifdef ECRYPT_GENERATES_KEYSTREAM_E_KSDC
	u8 ENCRYPT_grain_E_KSDC(
		ECRYPT_ctx* ctx);
#endif

#define ECRYPT_GENERATES_BACKWARD_KEYSTREAM_BIT
#ifdef	ECRYPT_GENERATES_BACKWARD_KEYSTREAM_BIT
	u8 ENCRYPT_grain_keystream_backward(
		ECRYPT_ctx* ctx);
#endif

#define ECRYPT_GENERATES_KEYSTREAM_BW_E_KSDC
#ifdef	ECRYPT_GENERATES_KEYSTREAM_BW_E_KSDC
	u8 ENCRYPT_grain_BW_E_KSDC(
		ECRYPT_ctx* ctx);
#endif

#define ECRYPT_GENERATES_KEYSTREAM
#ifdef ECRYPT_GENERATES_KEYSTREAM

void ECRYPT_keystream_bytes(
  ECRYPT_ctx* ctx,
  u8* keystream,
  u32 length);                /* Length of keystream in bytes. */

#endif

//kevin edit, for backward keystream generate
#define ECRYPT_GENERATES_BACKWARD_KEYSTREAM
#ifdef ECRYPT_GENERATES_BACKWARD_KEYSTREAM
void ECRYPT_keystream_backward_bytes(
  ECRYPT_ctx* ctx, 
  u8* keystream, 
  u32 msglen);				/* Length of keystream in bytes. */
#endif

#define ECRYPT_STATE_READ
#ifdef ECRYPT_STATE_READ
void ECRYPT_grain_state_read(
	ECRYPT_ctx* ctx, 
	u8* state);				 /*state in 20 bytes  */
#endif

#define ECRYPT_STATE_LOAD
#ifdef ECRYPT_STATE_LOAD
void ECRYPT_grain_state_load(
	ECRYPT_ctx* ctx, 
	u8* state);           /*state in 20 bytes  */
#endif

#define POSITION_INDEX
#ifdef POSITION_INDEX
	u32 posIdx(u32 pos);
#endif
#define ROTATE_INDEX
#ifdef ROTATE_INDEX
	u32 rotateIdx(u32 pos);
#endif

#define CONVERTOR_CHAR2HEXSTRING
#ifdef CONVERTOR_CHAR2HEXSTRING
	string char2HexString(
		u8* bArray,
		u32 bLen);
#endif

#define CONVERTOR_INT2STRING
#ifdef CONVERTOR_INT2STRING
	string int_2_string(int a);
#endif

#define CONVERTOR_MAKEDIR
#ifdef CONVERTOR_MAKEDIR
	void make_DIR(string curr_DIR);
#endif



//kevin edit
# define LEN 20					//20(byte)*8=160-bit 的内部状态
# define KSLen 10      // Length of keystream in bytes.
//# define T_NUM 50000			//每一组差分对应的测试用例的个数  也就是sampling的大小N
# define DIR "D:\\Grain_table_new\\"


//Grain_Q(n,d,l)_estimate_precompute_table_construction.cpp
void Q_estimate_precomputation(u32 d, u64* N_array, u64* sub_N_array);
void Q_estimate_combination_for_search_imp(u32 n,u32 k,u64 N, u64 sub_N, string curr_DIR);
bool Q_estimate_combin_for_search_imp_sub(u32 k,u32* v,u64 N, u64 sub_N,string curr_DIR);
void Q_estimate_genOutput_diff_imp(u32 k,u32 *v,u64 N,u64 sub_N, string curr_DIR);

//Grain_Q(n,d,l)_estimate_Random_Sampling
double Q_estimate_random_sampling(u32 d,u32 num_ISD,u64 N,u64 sub_N);

//Grain_ISD_Proportion_Test
void ISD_prop_test(u32 d,u32 num_ISD,u64 N,u32 sub_N);
int comp_struct_KSD_Prop(const void *a,const void *b);
typedef struct
{
	string KSD;
	u64 occurrance;
} KSD_Prop;
u32 HEAP_PARENT(u32 i);
u32 HEAP_LEFT(u32 i);
u32 HEAP_RIGHT(u32 i);
void HEAP_MIN_HEAPIFY(KSD_Prop* A,u32 i,u32 heap_size);
void BUILD_MIN_HEAP(KSD_Prop* A,u32 heap_size);

//Grain_E_KSDC_Martin_Simple_Compute
void average_fixed_pos_E_KSDC(u32 d,u32 num_ISD);
void E_KSDC_fixed_pos_with_given_ISD(u32 d,u32 *pos);
string E_KSDC_seq_with_given_ISD(u32 d,u32 *pos);
//Grain_BW-E_KSDC_Martin_Simple_Compute
string BW_E_KSDC_seq_with_given_ISD(u32 d,u32 *pos);
void average_fixed_pos_BW_E_KSDC(u32 d,u32 num_ISD);

//Grain_KSD_characteristic
bool isExist(u32 *pos,int j,u32 curr_val);
void ave_KSD_pos_with_fixed_diff(u32 d,u32 num_ISD,u32 N);
void KSD_pos_with_fixed_diff(u32 d,u32 *pos,u32 N);
string KSD_sequence_with_fixed_diff(u32 d,u32 *pos,u32 N);

void E_KSDC_enumerate_all_ISD(u32 d,u64 N);
void E_KSDC_enu_for_search(u32 n,u32 k,u64 N,string fileName);
bool E_KSDC_enu_for_search_sub(u32 k,u32 *v,u64 N,string fileName);
void E_KSDC_calculation(u32 k,u32 *v,u64 N,string fileName);


//Grain_KSD_backward_characteristic
void BW_ave_KSD_pos_with_fixed_diff(u32 d,u32 num_ISD,u32 N);
void BW_KSD_pos_with_fixed_diff(u32 d,u32 *pos,u32 num_ISD,u32 N);
string BW_KSD_seq_with_fixed_diff(u32 d,u32 *pos,u32 N);

//Grain_KSD_backward_characteristic_with_sampling_resistance
void BW_ave_KSD_pos_with_fixed_diff_with_SP(u32 d,u32 num_ISD,u32 N);
bool isExistWithSP_BW(u32 *pos,int j,u32 curr_val,u32 range);

//RC4 random generate
void rc4_setup();
u8 rc4();
void randomIV(u32 *iv);
int intcmp(const void *v1, const void *v2);


//Grain_KSD_Nums
void cal_all_KSD_construct_table(u32 d, u64* N_array);
void combination_for_search_imp(u32 n,u32 k,u64 N, string curr_DIR);
bool combin_for_search_imp_sub(u32 k,u32* v,u64 N,string curr_DIR);
void genOutput_diff_imp(u32 k,u32 *v,u64 N,string curr_DIR);


//Grain_KSD_Nums_Random_Sampling.cpp
double cal_all_KSD_with_Random_Sampling(u32 d, u64* N_array, u32 num_ISD);

//Grain_near_collision_validates.cpp
u32 validate_d_near_collision(u32 d,u64 D,u32 step);
bool validate_d_near_collision_non_reuse(u32 d,u64 H,u32 step);
typedef struct
{
	u8 STATE[LEN];
	u64 clock_t;
} State_array;
u32 validate_d_near_collision_Lemma_1(u32 d,u64 D,u32 step);

//Grain_v1_with_sampling_resistance.cpp
//void grain_v1_sampling_resistance(ECRYPT_ctx* ctx,u32 *L,u32 *N);
void grain_v1_sampling_resistance(ECRYPT_ctx* ctx,u8 *IS);
void grain_sampling_resistance_genKSBytes(ECRYPT_ctx* ctx,
  u8* keystream,
  u32 length);

//Grain_KSD_characteristic_with_sampling_resistance.cpp
bool isExistWithSP(u32 *pos,int j,u32 curr_val,u32 range);
void ave_KSD_pos_with_fixed_diff_with_SP(u32 d,u32 num_ISD,u32 N);