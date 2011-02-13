/*===========================================================================*/
/*   (work-queue.scm)                                                        */
/*   Bigloo (3.5a)                                                           */
/*   Inria -- Sophia Antipolis (c)       Sat Nov 6 18:30:31 EDT 2010         */
/*===========================================================================*/
/* COMPILATION: (bigloo -Obench -cgen work-queue.scm)*/
/* GC selection */
#define THE_GC BOEHM_GC

#include <bigloo.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Object type definitions */
typedef struct BgL_threadz00_bgl {
   header_t header;
   obj_t widening;
   obj_t BgL_namez00;
} *BgL_threadz00_bglt;

typedef struct BgL_pthreadz00_bgl {
   header_t header;
   obj_t widening;
   obj_t BgL_namez00;
   obj_t BgL_bodyz00;
   bool_t BgL_detachedpz00;
   obj_t BgL_endzd2resultzd2;
   obj_t BgL_endzd2exceptionzd2;
   void * BgL_z42builtinz42;
} *BgL_pthreadz00_bglt;

typedef struct BgL_z52workzd2queuezd2itemz52_bgl {
   header_t header;
   obj_t widening;
   obj_t BgL_thunkz00;
   struct BgL_z52workzd2queuezd2itemz52_bgl * BgL_nextz00;
} *BgL_z52workzd2queuezd2itemz52_bglt;

typedef struct BgL_z52workzd2queuez80_bgl {
   header_t header;
   obj_t widening;
   obj_t BgL_maxzd2threadszd2;
   obj_t BgL_idlezd2threadszd2;
   obj_t BgL_currentzd2threadszd2;
   obj_t BgL_finishz00;
   obj_t BgL_mutexz00;
   obj_t BgL_conditionzd2variablezd2;
   struct BgL_z52workzd2queuezd2itemz52_bgl * BgL_firstz00;
   struct BgL_z52workzd2queuezd2itemz52_bgl * BgL_lastz00;
} *BgL_z52workzd2queuez80_bglt;


static obj_t BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2 = BUNSPEC;
static obj_t BGl__z52workzd2queuezd2lastz52zzworkzd2queuezd2(obj_t, obj_t);
BGL_IMPORT obj_t BGl_threadzd2startz12zc0zz__threadz00(BgL_threadz00_bglt, obj_t);
static obj_t BGl__workzd2queuezd2pushz12z12zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(obj_t);
static obj_t BGl__makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2(obj_t, obj_t, obj_t);
BGL_IMPORT long BGl_classzd2numzd2zz__objectz00(obj_t);
static long BGl_zb2workzd2waitzd2timezb2z00zzworkzd2queuezd2;
static obj_t BGl_zc3anonymousza31724ze3z83zzworkzd2queuezd2(obj_t);
BGL_IMPORT void * BGl_z42pthreadzd2nilz90zz__pth_threadz00();
BGL_IMPORT obj_t BGl_readz00zz__readerz00(obj_t, obj_t);
BGL_IMPORT bool_t BGl_iszd2azf3z21zz__objectz00(obj_t, obj_t);
static obj_t BGl_requirezd2initializa7ationz75zzworkzd2queuezd2 = BUNSPEC;
static obj_t BGl_zc3anonymousza31727ze3z83zzworkzd2queuezd2(obj_t);
static obj_t BGl_genericzd2initzd2zzworkzd2queuezd2();
BGL_IMPORT obj_t BGl_objectz00zz__objectz00;
BGL_EXPORTED_DECL obj_t BGl_makezd2workzd2queuez00zzworkzd2queuezd2(obj_t);
BGL_IMPORT obj_t BGl_registerzd2classz12zc0zz__objectz00(obj_t, obj_t, bool_t, obj_t, obj_t, obj_t, obj_t, long, obj_t, obj_t, obj_t);
BGL_IMPORT void bgl_sleep(long);
BGL_IMPORT obj_t BGl_gensymz00zz__r4_symbols_6_4z00(obj_t);
static obj_t BGl__z52workzd2queuezd2lastzd2setz12z92zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__workzd2queuezd2finishz12z12zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2maxzd2threadszd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static BgL_z52workzd2queuez80_bglt BGl_makezd2z52workzd2queuez52zzworkzd2queuezd2(obj_t, obj_t, obj_t, obj_t, obj_t, obj_t, BgL_z52workzd2queuezd2itemz52_bglt, BgL_z52workzd2queuezd2itemz52_bglt);
BGL_IMPORT obj_t BGl_makezd2classzd2fieldz00zz__objectz00(obj_t, obj_t, obj_t, obj_t, bool_t, obj_t, obj_t);
static obj_t BGl_z52workzd2queuez80zzworkzd2queuezd2 = BUNSPEC;
static obj_t BGl_cnstzd2initzd2zzworkzd2queuezd2();
static obj_t BGl__z52workzd2queuezd2idlezd2threadsz80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__makezd2workzd2queuez00zzworkzd2queuezd2(obj_t, obj_t);
BGL_EXPORTED_DECL obj_t BGl_workzd2queuezd2finishz12z12zzworkzd2queuezd2(obj_t);
static obj_t BGl__z52workzd2queuezd2itemzf3za1zzworkzd2queuezd2(obj_t, obj_t);
BGL_IMPORT obj_t bgl_display_obj(obj_t, obj_t);
static obj_t BGl_zc3anonymousza31759ze3z83zzworkzd2queuezd2(obj_t);
static obj_t BGl__z52workzd2queuezd2itemzd2nextz80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2finishz52zzworkzd2queuezd2(obj_t, obj_t);
BGL_IMPORT obj_t make_struct(obj_t, int, obj_t);
BGL_IMPORT obj_t BGl_withzd2lockzd2zz__threadz00(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2maxzd2threadsz80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezf3z73zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl_zc3anonymousza31767ze3z83zzworkzd2queuezd2(obj_t);
static obj_t BGl__z52workzd2queuezd2firstz52zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2mutexzd2setz12z92zzworkzd2queuezd2(obj_t, obj_t, obj_t);
BGL_IMPORT obj_t bgl_display_string(obj_t, obj_t);
BGL_IMPORT obj_t BGl_2zb2zb2zz__r4_numbers_6_5z00(obj_t, obj_t);
BGL_IMPORT obj_t BGl_2zd2zd2zz__r4_numbers_6_5z00(obj_t, obj_t);
BGL_IMPORT bool_t BGl_2zc3zc3zz__r4_numbers_6_5z00(obj_t, obj_t);
BGL_IMPORT bool_t BGl_2ze3ze3zz__r4_numbers_6_5z00(obj_t, obj_t);
static BgL_z52workzd2queuezd2itemz52_bglt BGl_makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2(obj_t, BgL_z52workzd2queuezd2itemz52_bglt);
BGL_EXPORTED_DECL obj_t BGl_modulezd2initializa7ationz75zzworkzd2queuezd2(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__pth_threadz00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__r4_output_6_10_3z00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__r4_numbers_6_5z00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__r4_symbols_6_4z00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__r4_pairs_and_lists_6_3z00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__readerz00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__threadz00(long, char *);
BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__objectz00(long, char *);
static obj_t BGl__z52allocatezd2z52workzd2queuezd2itemzd2zzworkzd2queuezd2(obj_t);
static obj_t BGl_toplevelzd2initzd2zzworkzd2queuezd2();
static obj_t BGl__z52workzd2queuezd2currentzd2threadszd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2conditionzd2variablezd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl_makezd2workzd2queuezd2threadzd2thunkz00zzworkzd2queuezd2(obj_t);
BGL_IMPORT obj_t BGl_addzd2methodz12zc0zz__objectz00(obj_t, obj_t, obj_t);
static obj_t BGl_objectzd2ze3structzd2z52work1705zb1zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl_objectzd2ze3structzd2z52work1709zb1zzworkzd2queuezd2(obj_t, obj_t);
BGL_EXPORTED_DECL obj_t BGl_workzd2queuezd2pushz12z12zzworkzd2queuezd2(obj_t, obj_t);
static BgL_z52workzd2queuez80_bglt BGl_z52workzd2queuezd2nilz52zzworkzd2queuezd2();
BGL_IMPORT obj_t bgl_open_input_string(obj_t, int);
static obj_t BGl__z52allocatezd2z52workzd2queuez00zzworkzd2queuezd2(obj_t);
static obj_t BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2 = BUNSPEC;
BGL_IMPORT BgL_pthreadz00_bglt BGl_makezd2pthreadzd2zz__pth_threadz00(obj_t, obj_t, bool_t, obj_t, obj_t, void *);
static obj_t BGl__z52workzd2queuezd2itemzd2thunkz80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2idlezd2threadszd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__makezd2z52workzd2queuez52zzworkzd2queuezd2(obj_t, obj_t, obj_t, obj_t, obj_t, obj_t, obj_t, obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2itemzd2thunkzd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2nilz52zzworkzd2queuezd2(obj_t);
static obj_t BGl_structzb2objectzd2ze3objec1707z83zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl_structzb2objectzd2ze3objec1711z83zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2 = BUNSPEC;
static obj_t BGl__z52workzd2queuezd2conditionzd2variablez80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2currentzd2threadsz80zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2firstzd2setz12z92zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl__z52workzd2queuezd2mutexz52zzworkzd2queuezd2(obj_t, obj_t);
static obj_t BGl_objectzd2initzd2zzworkzd2queuezd2();
static obj_t BGl__z52workzd2queuezd2finishzd2setz12z92zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl_libraryzd2moduleszd2initz00zzworkzd2queuezd2();
static obj_t BGl__z52workzd2queuezd2itemzd2nextzd2setz12z40zzworkzd2queuezd2(obj_t, obj_t, obj_t);
static obj_t BGl_methodzd2initzd2zzworkzd2queuezd2();
BGL_IMPORT obj_t BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00();
static BgL_z52workzd2queuezd2itemz52_bglt BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2();
static obj_t __cnst[ 13 ] ;


DEFINE_STATIC_BGL_PROCEDURE( BGl_makezd2z52workzd2queuezd2itemzd2envz52zzworkzd2queuezd2, BgL_bgl__makeza7d2za752workza71925za7, BGl__makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2finishzd2setz12zd2envz40zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1926z00, BGl__z52workzd2queuezd2finishzd2setz12z92zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzd2nilzd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1927z00, BGl__z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2, 0L, BUNSPEC, 0 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2currentzd2threadszd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1928z00, BGl__z52workzd2queuezd2currentzd2threadsz80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2finishzd2envz80zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1929z00, BGl__z52workzd2queuezd2finishz52zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_makezd2z52workzd2queuezd2envz80zzworkzd2queuezd2, BgL_bgl__makeza7d2za752workza71930za7, BGl__makezd2z52workzd2queuez52zzworkzd2queuezd2, 0L, BUNSPEC, 8 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2idlezd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1931z00, BGl__z52workzd2queuezd2idlezd2threadszd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2firstzd2envz80zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1932z00, BGl__z52workzd2queuezd2firstz52zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2maxzd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1933z00, BGl__z52workzd2queuezd2maxzd2threadszd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2maxzd2threadszd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1934z00, BGl__z52workzd2queuezd2maxzd2threadsz80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2mutexzd2setz12zd2envz40zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1935z00, BGl__z52workzd2queuezd2mutexzd2setz12z92zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezf3zd2envza1zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1936z00, BGl__z52workzd2queuezf3z73zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52allocatezd2z52workzd2queuezd2itemzd2envz00zzworkzd2queuezd2, BgL_bgl__za752allocateza7d2za71937za7, BGl__z52allocatezd2z52workzd2queuezd2itemzd2zzworkzd2queuezd2, 0L, BUNSPEC, 0 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52allocatezd2z52workzd2queuezd2envzd2zzworkzd2queuezd2, BgL_bgl__za752allocateza7d2za71938za7, BGl__z52allocatezd2z52workzd2queuez00zzworkzd2queuezd2, 0L, BUNSPEC, 0 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2lastzd2envz80zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1939z00, BGl__z52workzd2queuezd2lastz52zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_EXPORT_BGL_PROCEDURE( BGl_workzd2queuezd2pushz12zd2envzc0zzworkzd2queuezd2, BgL_bgl__workza7d2queueza7d21940z00, BGl__workzd2queuezd2pushz12z12zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
BGL_IMPORT obj_t BGl_conszd2envzd2zz__r4_pairs_and_lists_6_3z00;
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2currentzd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1941z00, BGl__z52workzd2queuezd2currentzd2threadszd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2lastzd2setz12zd2envz40zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1942z00, BGl__z52workzd2queuezd2lastzd2setz12z92zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_proc1916z00zzworkzd2queuezd2, BgL_bgl_objectza7d2za7e3stru1943z00, BGl_objectzd2ze3structzd2z52work1705zb1zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_proc1917z00zzworkzd2queuezd2, BgL_bgl_structza7b2objectza71944z00, BGl_structzb2objectzd2ze3objec1707z83zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_proc1918z00zzworkzd2queuezd2, BgL_bgl_objectza7d2za7e3stru1945z00, BGl_objectzd2ze3structzd2z52work1709zb1zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_proc1919z00zzworkzd2queuezd2, BgL_bgl_structza7b2objectza71946z00, BGl_structzb2objectzd2ze3objec1711z83zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2mutexzd2envz80zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1947z00, BGl__z52workzd2queuezd2mutexz52zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzd2nextzd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1948z00, BGl__z52workzd2queuezd2itemzd2nextzd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2conditionzd2variablezd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1949z00, BGl__z52workzd2queuezd2conditionzd2variablez80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STRING( BGl_string1912z00zzworkzd2queuezd2, BgL_bgl_string1912za700za7za7w1950za7, "work-queue.scm", 14 );
DEFINE_STRING( BGl_string1913z00zzworkzd2queuezd2, BgL_bgl_string1913za700za7za7w1951za7, "cond res: ", 10 );
DEFINE_STRING( BGl_string1914z00zzworkzd2queuezd2, BgL_bgl_string1914za700za7za7w1952za7, "signal received", 15 );
DEFINE_STRING( BGl_string1915z00zzworkzd2queuezd2, BgL_bgl_string1915za700za7za7w1953za7, "timed out", 9 );
DEFINE_STRING( BGl_string1920z00zzworkzd2queuezd2, BgL_bgl_string1920za700za7za7w1954za7, "last first finish current-threads idle-threads max-threads %work-queue next thunk %work-queue-item thread condition-variable mutex ", 131 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzd2thunkzd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1955z00, BGl__z52workzd2queuezd2itemzd2thunkzd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzd2nextzd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1956z00, BGl__z52workzd2queuezd2itemzd2nextz80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2conditionzd2variablezd2setz12zd2envz92zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1957z00, BGl__z52workzd2queuezd2conditionzd2variablezd2setz12z40zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2nilzd2envz80zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1958z00, BGl__z52workzd2queuezd2nilz52zzworkzd2queuezd2, 0L, BUNSPEC, 0 );
DEFINE_EXPORT_BGL_PROCEDURE( BGl_makezd2workzd2queuezd2envzd2zzworkzd2queuezd2, BgL_bgl__makeza7d2workza7d2q1959z00, BGl__makezd2workzd2queuez00zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzf3zd2envz73zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1960z00, BGl__z52workzd2queuezd2itemzf3za1zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2idlezd2threadszd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1961z00, BGl__z52workzd2queuezd2idlezd2threadsz80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_EXPORT_BGL_PROCEDURE( BGl_workzd2queuezd2finishz12zd2envzc0zzworkzd2queuezd2, BgL_bgl__workza7d2queueza7d21962z00, BGl__workzd2queuezd2finishz12z12zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
BGL_IMPORT obj_t BGl_objectzd2ze3structzd2envze3zz__objectz00;
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2itemzd2thunkzd2envz52zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1963z00, BGl__z52workzd2queuezd2itemzd2thunkz80zzworkzd2queuezd2, 0L, BUNSPEC, 1 );
DEFINE_STATIC_BGL_PROCEDURE( BGl_z52workzd2queuezd2firstzd2setz12zd2envz40zzworkzd2queuezd2, BgL_bgl__za752workza7d2queue1964z00, BGl__z52workzd2queuezd2firstzd2setz12z92zzworkzd2queuezd2, 0L, BUNSPEC, 2 );
BGL_IMPORT obj_t BGl_structzb2objectzd2ze3objectzd2envz51zz__objectz00;



/* module-initialization */
BGL_EXPORTED_DEF obj_t BGl_modulezd2initializa7ationz75zzworkzd2queuezd2(long BgL_checksumz00_922, char * BgL_fromz00_923)
{ AN_OBJECT;
{ 
if(
CBOOL(BGl_requirezd2initializa7ationz75zzworkzd2queuezd2))
{ 
BGl_requirezd2initializa7ationz75zzworkzd2queuezd2 = 
BBOOL(((bool_t)0)); 
BGl_libraryzd2moduleszd2initz00zzworkzd2queuezd2(); 
BGl_cnstzd2initzd2zzworkzd2queuezd2(); 
BGl_objectzd2initzd2zzworkzd2queuezd2(); 
BGl_methodzd2initzd2zzworkzd2queuezd2(); 
BGl_toplevelzd2initzd2zzworkzd2queuezd2(); 
return BUNSPEC;}  else 
{ 
return BUNSPEC;} } 
}



/* library-modules-init */
obj_t BGl_libraryzd2moduleszd2initz00zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
BGl_modulezd2initializa7ationz75zz__threadz00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__objectz00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__pth_threadz00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__readerz00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__r4_symbols_6_4z00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__r4_output_6_10_3z00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__r4_pairs_and_lists_6_3z00(((long)0), "work-queue"); 
BGl_modulezd2initializa7ationz75zz__r4_numbers_6_5z00(((long)0), "work-queue"); 
return BUNSPEC;} 
}



/* cnst-init */
obj_t BGl_cnstzd2initzd2zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
{ /* work-queue.scm 33 */
obj_t BgL_cportz00_872;
BgL_cportz00_872 = 
bgl_open_input_string(BGl_string1920z00zzworkzd2queuezd2, 
(int)(((long)0))); 
{ 
long BgL_iz00_873;
BgL_iz00_873 = ((long)12); 
BgL_loopz00_874:
if(
(BgL_iz00_873==((long)-1)))
{ /* work-queue.scm 33 */
return BUNSPEC;}  else 
{ /* work-queue.scm 33 */
{ /* work-queue.scm 33 */
obj_t BgL_arg1922z00_876;
{ /* work-queue.scm 33 */

{ /* work-queue.scm 33 */
obj_t BgL_locationz00_878;
BgL_locationz00_878 = 
BBOOL(((bool_t)0)); 
{ /* work-queue.scm 33 */

BgL_arg1922z00_876 = 
BGl_readz00zz__readerz00(BgL_cportz00_872, BgL_locationz00_878); } } } 
{ /* work-queue.scm 33 */
int BgL_auxz00_946;
BgL_auxz00_946 = 
(int)(BgL_iz00_873); 
CNST_TABLE_SET(BgL_auxz00_946, BgL_arg1922z00_876); } } 
{ /* work-queue.scm 33 */
int BgL_auxz00_879;
BgL_auxz00_879 = 
(int)(
(BgL_iz00_873-((long)1))); 
{ 
long BgL_iz00_951;
BgL_iz00_951 = 
(long)(BgL_auxz00_879); 
BgL_iz00_873 = BgL_iz00_951; 
goto BgL_loopz00_874;} } } } } } 
}



/* toplevel-init */
obj_t BGl_toplevelzd2initzd2zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
BGl_modulezd2initializa7ationz75zz__pth_threadz00(((long)0), 
BSTRING_TO_STRING(BGl_string1912z00zzworkzd2queuezd2)); 
return ( 
BGl_zb2workzd2waitzd2timezb2z00zzworkzd2queuezd2 = ((long)60000), BUNSPEC) ;} 
}



/* make-work-queue */
BGL_EXPORTED_DEF obj_t BGl_makezd2workzd2queuez00zzworkzd2queuezd2(obj_t BgL_maxzd2threadszd2_1)
{ AN_OBJECT;
{ /* work-queue.scm 54 */
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_nwqz00_397;
{ /* work-queue.scm 60 */
obj_t BgL_arg1716z00_400;obj_t BgL_arg1718z00_401;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1719z00_402;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1721z00_403;
{ /* work-queue.scm 60 */

{ /* work-queue.scm 60 */
obj_t BgL_namez00_404;
BgL_namez00_404 = 
BGl_gensymz00zz__r4_symbols_6_4z00(
CNST_TABLE_REF(((long)0))); 
{ /* work-queue.scm 60 */

BgL_arg1716z00_400 = 
bgl_make_mutex(BgL_namez00_404); } } } 
{ /* work-queue.scm 60 */

{ /* work-queue.scm 60 */
obj_t BgL_namez00_405;
BgL_namez00_405 = 
BGl_gensymz00zz__r4_symbols_6_4z00(
CNST_TABLE_REF(((long)1))); 
{ /* work-queue.scm 60 */

BgL_arg1718z00_401 = 
bgl_make_condvar(BgL_namez00_405); } } } 
BgL_arg1719z00_402 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
BgL_arg1721z00_403 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_res1889z00_440;
{ /* work-queue.scm 60 */
obj_t BgL_idlezd2threads1623zd2_409;obj_t BgL_currentzd2threads1624zd2_410;
BgL_idlezd2threads1623zd2_409 = 
BINT(((long)0)); 
BgL_currentzd2threads1624zd2_410 = 
BINT(((long)0)); 
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_new1630z00_416;
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_res1887z00_421;
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_new1650z00_417;
BgL_new1650z00_417 = 
((BgL_z52workzd2queuez80_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuez80_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1650z00_417), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuez80zzworkzd2queuezd2)); 
{ /* work-queue.scm 60 */
BgL_objectz00_bglt BgL_auxz00_969;
BgL_auxz00_969 = 
(BgL_objectz00_bglt)(BgL_new1650z00_417); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_969, BFALSE); } 
BgL_res1887z00_421 = BgL_new1650z00_417; } 
BgL_new1630z00_416 = BgL_res1887z00_421; } 
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_res1888z00_439;
{ /* work-queue.scm 60 */
BgL_z52workzd2queuez80_bglt BgL_new1640z00_422;
BgL_new1640z00_422 = BgL_new1630z00_416; 
{ /* work-queue.scm 60 */
obj_t BgL_maxzd2threads1632zd2_431;obj_t BgL_idlezd2threads1633zd2_432;obj_t BgL_currentzd2threads1634zd2_433;obj_t BgL_finish1635z00_434;obj_t BgL_mutex1636z00_435;obj_t BgL_conditionzd2variable1637zd2_436;BgL_z52workzd2queuezd2itemz52_bglt BgL_first1638z00_437;BgL_z52workzd2queuezd2itemz52_bglt BgL_last1639z00_438;
BgL_maxzd2threads1632zd2_431 = BgL_maxzd2threadszd2_1; 
BgL_idlezd2threads1633zd2_432 = BgL_idlezd2threads1623zd2_409; 
BgL_currentzd2threads1634zd2_433 = BgL_currentzd2threads1624zd2_410; 
BgL_finish1635z00_434 = BFALSE; 
BgL_mutex1636z00_435 = BgL_arg1716z00_400; 
BgL_conditionzd2variable1637zd2_436 = BgL_arg1718z00_401; 
BgL_first1638z00_437 = BgL_arg1719z00_402; 
BgL_last1639z00_438 = BgL_arg1721z00_403; 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_maxzd2threadszd2) = ((obj_t)BgL_maxzd2threads1632zd2_431), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_idlezd2threadszd2) = ((obj_t)BgL_idlezd2threads1633zd2_432), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_currentzd2threadszd2) = ((obj_t)BgL_currentzd2threads1634zd2_433), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_finishz00) = ((obj_t)BgL_finish1635z00_434), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_mutexz00) = ((obj_t)BgL_mutex1636z00_435), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_conditionzd2variablezd2) = ((obj_t)BgL_conditionzd2variable1637zd2_436), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_first1638z00_437), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_422))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_last1639z00_438), BUNSPEC); 
BgL_res1888z00_439 = BgL_new1640z00_422; } } BgL_res1888z00_439; } 
BgL_res1889z00_440 = BgL_new1630z00_416; } } 
BgL_nwqz00_397 = BgL_res1889z00_440; } } 
{ /* work-queue.scm 60 */

return 
(obj_t)(BgL_nwqz00_397);} } } 
}



/* _make-work-queue */
obj_t BGl__makezd2workzd2queuez00zzworkzd2queuezd2(obj_t BgL_envz00_759, obj_t BgL_maxzd2threadszd2_760)
{ AN_OBJECT;
{ /* work-queue.scm 54 */
return 
BGl_makezd2workzd2queuez00zzworkzd2queuezd2(BgL_maxzd2threadszd2_760);} 
}



/* make-work-queue-thread-thunk */
obj_t BGl_makezd2workzd2queuezd2threadzd2thunkz00zzworkzd2queuezd2(obj_t BgL_queuez00_3)
{ AN_OBJECT;
{ /* work-queue.scm 73 */
{ /* work-queue.scm 102 */
obj_t BgL_zc3anonymousza31724ze3z83_762;
BgL_zc3anonymousza31724ze3z83_762 = 
make_fx_procedure(BGl_zc3anonymousza31724ze3z83zzworkzd2queuezd2, 
(int)(((long)0)), 
(int)(((long)1))); 
PROCEDURE_SET(BgL_zc3anonymousza31724ze3z83_762, 
(int)(((long)0)), BgL_queuez00_3); 
return BgL_zc3anonymousza31724ze3z83_762;} } 
}



/* <anonymous:1724> */
obj_t BGl_zc3anonymousza31724ze3z83zzworkzd2queuezd2(obj_t BgL_envz00_763)
{ AN_OBJECT;
{ /* work-queue.scm 102 */
{ /* work-queue.scm 103 */
obj_t BgL_queuez00_764;
BgL_queuez00_764 = 
PROCEDURE_REF(BgL_envz00_763, 
(int)(((long)0))); 
{ 

{ /* work-queue.scm 103 */
obj_t BgL_arg1725z00_181;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_989;
BgL_auxz00_989 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_764); 
BgL_arg1725z00_181 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_989))->BgL_mutexz00); } 
{ /* work-queue.scm 105 */
obj_t BgL_zc3anonymousza31727ze3z83_761;
BgL_zc3anonymousza31727ze3z83_761 = 
make_fx_procedure(BGl_zc3anonymousza31727ze3z83zzworkzd2queuezd2, 
(int)(((long)0)), 
(int)(((long)1))); 
PROCEDURE_SET(BgL_zc3anonymousza31727ze3z83_761, 
(int)(((long)0)), BgL_queuez00_764); 
return 
BGl_withzd2lockzd2zz__threadz00(BgL_arg1725z00_181, BgL_zc3anonymousza31727ze3z83_761);} } } } } 
}



/* <anonymous:1727> */
obj_t BGl_zc3anonymousza31727ze3z83zzworkzd2queuezd2(obj_t BgL_envz00_765)
{ AN_OBJECT;
{ /* work-queue.scm 104 */
{ /* work-queue.scm 105 */
obj_t BgL_queuez00_766;
BgL_queuez00_766 = 
PROCEDURE_REF(BgL_envz00_765, 
(int)(((long)0))); 
{ 

{ 
obj_t BgL_queuez00_201;
{ /* work-queue.scm 105 */
obj_t BgL_g1690z00_184;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1000;
BgL_auxz00_1000 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
BgL_g1690z00_184 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1000))->BgL_finishz00); } 
{ 
obj_t BgL_finishz00_186;
BgL_finishz00_186 = BgL_g1690z00_184; 
BgL_zc3anonymousza31728ze3z83_187:
{ /* work-queue.scm 106 */
bool_t BgL_testz00_1003;
if(
CBOOL(BgL_finishz00_186))
{ /* work-queue.scm 106 */
BgL_testz00_1003 = ((bool_t)0)
; }  else 
{ /* work-queue.scm 106 */
BgL_queuez00_201 = BgL_queuez00_766; 
{ /* work-queue.scm 75 */
bool_t BgL_g1689z00_203;
{ /* work-queue.scm 75 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1722z00_473;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1723z00_474;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1006;
BgL_auxz00_1006 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_arg1722z00_473 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1006))->BgL_firstz00); } 
BgL_arg1723z00_474 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
BgL_g1689z00_203 = 
(
(obj_t)(BgL_arg1722z00_473)==
(obj_t)(BgL_arg1723z00_474)); } 
{ 
bool_t BgL_emptyzf3zf3_205;
BgL_emptyzf3zf3_205 = BgL_g1689z00_203; 
BgL_zc3anonymousza31738ze3z83_206:
if(BgL_emptyzf3zf3_205)
{ /* work-queue.scm 76 */
{ /* work-queue.scm 80 */
obj_t BgL_arg1739z00_207;
{ /* work-queue.scm 80 */
obj_t BgL_auxz00_1014;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1015;
BgL_auxz00_1015 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_auxz00_1014 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1015))->BgL_idlezd2threadszd2); } 
BgL_arg1739z00_207 = 
BGl_2zb2zb2zz__r4_numbers_6_5z00(BgL_auxz00_1014, 
BINT(((long)1))); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1020;
BgL_auxz00_1020 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1020))->BgL_idlezd2threadszd2) = ((obj_t)BgL_arg1739z00_207), BUNSPEC); } } 
{ /* work-queue.scm 81 */
bool_t BgL_resz00_210;
{ /* work-queue.scm 82 */
obj_t BgL_arg1753z00_222;obj_t BgL_arg1756z00_223;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1023;
BgL_auxz00_1023 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_arg1753z00_222 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1023))->BgL_conditionzd2variablezd2); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1026;
BgL_auxz00_1026 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_arg1756z00_223 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1026))->BgL_mutexz00); } 
{ /* work-queue.scm 81 */
bool_t BgL_res1891z00_487;
{ /* work-queue.scm 81 */
obj_t BgL_cz00_481;obj_t BgL_mz00_482;long BgL_timeoutz00_483;
BgL_cz00_481 = BgL_arg1753z00_222; 
BgL_mz00_482 = BgL_arg1756z00_223; 
BgL_timeoutz00_483 = BGl_zb2workzd2waitzd2timezb2z00zzworkzd2queuezd2; 
if(
(BgL_timeoutz00_483==((long)0)))
{ /* work-queue.scm 81 */
BgL_res1891z00_487 = 
bgl_condvar_wait(BgL_cz00_481, BgL_mz00_482); }  else 
{ /* work-queue.scm 81 */
BgL_res1891z00_487 = 
bgl_condvar_timed_wait(BgL_cz00_481, BgL_mz00_482, BgL_timeoutz00_483); } } 
BgL_resz00_210 = BgL_res1891z00_487; } } 
{ /* work-queue.scm 86 */
obj_t BgL_port1698z00_211;
{ /* work-queue.scm 86 */
obj_t BgL_res1892z00_489;
{ /* work-queue.scm 86 */
obj_t BgL_auxz00_1033;
BgL_auxz00_1033 = 
BGL_CURRENT_DYNAMIC_ENV(); 
BgL_res1892z00_489 = 
BGL_ENV_CURRENT_OUTPUT_PORT(BgL_auxz00_1033); } 
BgL_port1698z00_211 = BgL_res1892z00_489; } 
bgl_display_string(BGl_string1913z00zzworkzd2queuezd2, BgL_port1698z00_211); 
bgl_display_obj(
BBOOL(BgL_resz00_210), BgL_port1698z00_211); 
bgl_display_char(((unsigned char)'\n'), BgL_port1698z00_211); } 
{ /* work-queue.scm 87 */
obj_t BgL_port1699z00_212;
{ /* work-queue.scm 87 */
obj_t BgL_res1893z00_494;
{ /* work-queue.scm 87 */
obj_t BgL_auxz00_1040;
BgL_auxz00_1040 = 
BGL_CURRENT_DYNAMIC_ENV(); 
BgL_res1893z00_494 = 
BGL_ENV_CURRENT_OUTPUT_PORT(BgL_auxz00_1040); } 
BgL_port1699z00_212 = BgL_res1893z00_494; } 
bgl_display_obj(
BINT(BGl_zb2workzd2waitzd2timezb2z00zzworkzd2queuezd2), BgL_port1699z00_212); 
bgl_display_char(((unsigned char)'\n'), BgL_port1699z00_212); } 
if(BgL_resz00_210)
{ /* work-queue.scm 88 */
{ /* work-queue.scm 96 */
obj_t BgL_port1701z00_213;
{ /* work-queue.scm 96 */
obj_t BgL_res1894z00_497;
{ /* work-queue.scm 96 */
obj_t BgL_auxz00_1047;
BgL_auxz00_1047 = 
BGL_CURRENT_DYNAMIC_ENV(); 
BgL_res1894z00_497 = 
BGL_ENV_CURRENT_OUTPUT_PORT(BgL_auxz00_1047); } 
BgL_port1701z00_213 = BgL_res1894z00_497; } 
bgl_display_string(BGl_string1914z00zzworkzd2queuezd2, BgL_port1701z00_213); 
bgl_display_char(((unsigned char)'\n'), BgL_port1701z00_213); } 
{ /* work-queue.scm 98 */
obj_t BgL_arg1742z00_214;
{ /* work-queue.scm 98 */
obj_t BgL_auxz00_1052;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1053;
BgL_auxz00_1053 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_auxz00_1052 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1053))->BgL_idlezd2threadszd2); } 
BgL_arg1742z00_214 = 
BGl_2zd2zd2zz__r4_numbers_6_5z00(BgL_auxz00_1052, 
BINT(((long)1))); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1058;
BgL_auxz00_1058 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1058))->BgL_idlezd2threadszd2) = ((obj_t)BgL_arg1742z00_214), BUNSPEC); } } 
{ /* work-queue.scm 99 */
bool_t BgL_arg1746z00_217;
{ /* work-queue.scm 99 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1722z00_506;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1723z00_507;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1061;
BgL_auxz00_1061 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_arg1722z00_506 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1061))->BgL_firstz00); } 
BgL_arg1723z00_507 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
BgL_arg1746z00_217 = 
(
(obj_t)(BgL_arg1722z00_506)==
(obj_t)(BgL_arg1723z00_507)); } 
{ 
bool_t BgL_emptyzf3zf3_1068;
BgL_emptyzf3zf3_1068 = BgL_arg1746z00_217; 
BgL_emptyzf3zf3_205 = BgL_emptyzf3zf3_1068; 
goto BgL_zc3anonymousza31738ze3z83_206;} } }  else 
{ /* work-queue.scm 88 */
{ /* work-queue.scm 90 */
obj_t BgL_port1700z00_218;
{ /* work-queue.scm 90 */
obj_t BgL_res1895z00_510;
{ /* work-queue.scm 90 */
obj_t BgL_auxz00_1069;
BgL_auxz00_1069 = 
BGL_CURRENT_DYNAMIC_ENV(); 
BgL_res1895z00_510 = 
BGL_ENV_CURRENT_OUTPUT_PORT(BgL_auxz00_1069); } 
BgL_port1700z00_218 = BgL_res1895z00_510; } 
bgl_display_string(BGl_string1915z00zzworkzd2queuezd2, BgL_port1700z00_218); 
bgl_display_char(((unsigned char)'\n'), BgL_port1700z00_218); } 
{ /* work-queue.scm 93 */
obj_t BgL_arg1747z00_219;
{ /* work-queue.scm 93 */
obj_t BgL_auxz00_1074;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1075;
BgL_auxz00_1075 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
BgL_auxz00_1074 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1075))->BgL_idlezd2threadszd2); } 
BgL_arg1747z00_219 = 
BGl_2zd2zd2zz__r4_numbers_6_5z00(BgL_auxz00_1074, 
BINT(((long)1))); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1080;
BgL_auxz00_1080 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_201); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1080))->BgL_idlezd2threadszd2) = ((obj_t)BgL_arg1747z00_219), BUNSPEC); } } 
BgL_testz00_1003 = ((bool_t)0); } } }  else 
{ /* work-queue.scm 76 */
BgL_testz00_1003 = ((bool_t)1)
; } } } } 
if(BgL_testz00_1003)
{ /* work-queue.scm 106 */
{ /* work-queue.scm 109 */
obj_t BgL_thunk2z00_189;
{ /* work-queue.scm 109 */
BgL_z52workzd2queuez80_bglt BgL_queuez00_447;
BgL_queuez00_447 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
{ /* work-queue.scm 109 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_itemz00_449;
BgL_itemz00_449 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_queuez00_447))->BgL_firstz00); 
{ /* work-queue.scm 109 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1790z00_450;
BgL_arg1790z00_450 = 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_itemz00_449))->BgL_nextz00); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_queuez00_447))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_arg1790z00_450), BUNSPEC); } 
BgL_thunk2z00_189 = 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_itemz00_449))->BgL_thunkz00); } } 
{ /* work-queue.scm 110 */
obj_t BgL_arg1730z00_190;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1088;
BgL_auxz00_1088 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
BgL_arg1730z00_190 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1088))->BgL_mutexz00); } 
bgl_mutex_unlock(BgL_arg1730z00_190); } 
PROCEDURE_ENTRY(BgL_thunk2z00_189)(BgL_thunk2z00_189, BEOA); 
{ /* work-queue.scm 112 */
obj_t BgL_arg1731z00_191;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1094;
BgL_auxz00_1094 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
BgL_arg1731z00_191 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1094))->BgL_mutexz00); } 
{ /* work-queue.scm 112 */

{ /* work-queue.scm 112 */
obj_t BgL_mz00_459;
BgL_mz00_459 = BgL_arg1731z00_191; 
if(
(((long)0)==((long)0)))
{ /* work-queue.scm 112 */
bgl_mutex_lock(BgL_mz00_459); }  else 
{ /* work-queue.scm 112 */
bgl_mutex_timed_lock(BgL_mz00_459, ((long)0)); } } } } } 
{ /* work-queue.scm 113 */
obj_t BgL_arg1732z00_194;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1101;
BgL_auxz00_1101 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
BgL_arg1732z00_194 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1101))->BgL_finishz00); } 
{ 
obj_t BgL_finishz00_1104;
BgL_finishz00_1104 = BgL_arg1732z00_194; 
BgL_finishz00_186 = BgL_finishz00_1104; 
goto BgL_zc3anonymousza31728ze3z83_187;} } }  else 
{ /* work-queue.scm 106 */((bool_t)0); } } } } 
{ /* work-queue.scm 114 */
obj_t BgL_arg1733z00_196;
{ /* work-queue.scm 114 */
obj_t BgL_res1890z00_466;
{ /* work-queue.scm 114 */
obj_t BgL_auxz00_1105;
BgL_auxz00_1105 = 
BGL_CURRENT_DYNAMIC_ENV(); 
BgL_res1890z00_466 = 
BGL_ENV_CURRENT_OUTPUT_PORT(BgL_auxz00_1105); } 
BgL_arg1733z00_196 = BgL_res1890z00_466; } 
FLUSH_OUTPUT_PORT(BgL_arg1733z00_196); } 
{ /* work-queue.scm 117 */
obj_t BgL_arg1734z00_197;
{ /* work-queue.scm 117 */
obj_t BgL_auxz00_1109;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1110;
BgL_auxz00_1110 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
BgL_auxz00_1109 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1110))->BgL_currentzd2threadszd2); } 
BgL_arg1734z00_197 = 
BGl_2zd2zd2zz__r4_numbers_6_5z00(BgL_auxz00_1109, 
BINT(((long)1))); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1115;
BgL_auxz00_1115 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_766); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1115))->BgL_currentzd2threadszd2) = ((obj_t)BgL_arg1734z00_197), BUNSPEC);} } } } } } 
}



/* work-queue-finish! */
BGL_EXPORTED_DEF obj_t BGl_workzd2queuezd2finishz12z12zzworkzd2queuezd2(obj_t BgL_queuez00_4)
{ AN_OBJECT;
{ /* work-queue.scm 122 */
{ /* work-queue.scm 123 */
obj_t BgL_arg1757z00_226;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1118;
BgL_auxz00_1118 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_4); 
BgL_arg1757z00_226 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1118))->BgL_mutexz00); } 
{ /* work-queue.scm 125 */
obj_t BgL_zc3anonymousza31759ze3z83_767;
BgL_zc3anonymousza31759ze3z83_767 = 
make_fx_procedure(BGl_zc3anonymousza31759ze3z83zzworkzd2queuezd2, 
(int)(((long)0)), 
(int)(((long)1))); 
PROCEDURE_SET(BgL_zc3anonymousza31759ze3z83_767, 
(int)(((long)0)), BgL_queuez00_4); 
BGl_withzd2lockzd2zz__threadz00(BgL_arg1757z00_226, BgL_zc3anonymousza31759ze3z83_767); } } 
{ /* work-queue.scm 126 */
obj_t BgL_g1691z00_230;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1127;
BgL_auxz00_1127 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_4); 
BgL_g1691z00_230 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1127))->BgL_currentzd2threadszd2); } 
{ 
obj_t BgL_rtz00_522;
{ /* work-queue.scm 126 */
bool_t BgL_auxz00_1130;
BgL_rtz00_522 = BgL_g1691z00_230; 
BgL_loopz00_521:
if(
BGl_2ze3ze3zz__r4_numbers_6_5z00(BgL_rtz00_522, 
BINT(((long)0))))
{ /* work-queue.scm 126 */
bgl_sleep(((long)1000)); BUNSPEC; ((long)1000); 
{ /* work-queue.scm 126 */
obj_t BgL_arg1763z00_526;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1135;
BgL_auxz00_1135 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_4); 
BgL_arg1763z00_526 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1135))->BgL_currentzd2threadszd2); } 
{ 
obj_t BgL_rtz00_1138;
BgL_rtz00_1138 = BgL_arg1763z00_526; 
BgL_rtz00_522 = BgL_rtz00_1138; 
goto BgL_loopz00_521;} } }  else 
{ /* work-queue.scm 126 */
BgL_auxz00_1130 = ((bool_t)0)
; } 
return 
BBOOL(BgL_auxz00_1130);} } } } 
}



/* _work-queue-finish! */
obj_t BGl__workzd2queuezd2finishz12z12zzworkzd2queuezd2(obj_t BgL_envz00_768, obj_t BgL_queuez00_769)
{ AN_OBJECT;
{ /* work-queue.scm 122 */
return 
BGl_workzd2queuezd2finishz12z12zzworkzd2queuezd2(BgL_queuez00_769);} 
}



/* <anonymous:1759> */
obj_t BGl_zc3anonymousza31759ze3z83zzworkzd2queuezd2(obj_t BgL_envz00_770)
{ AN_OBJECT;
{ /* work-queue.scm 124 */
{ /* work-queue.scm 125 */
obj_t BgL_queuez00_771;
BgL_queuez00_771 = 
PROCEDURE_REF(BgL_envz00_770, 
(int)(((long)0))); 
{ 

{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1143;
BgL_auxz00_1143 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_771); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1143))->BgL_finishz00) = ((obj_t)BTRUE), BUNSPEC);} } } } 
}



/* work-queue-push! */
BGL_EXPORTED_DEF obj_t BGl_workzd2queuezd2pushz12z12zzworkzd2queuezd2(obj_t BgL_queuez00_5, obj_t BgL_thunk2z00_6)
{ AN_OBJECT;
{ /* work-queue.scm 131 */
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_nwiz00_238;
{ /* work-queue.scm 141 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1789z00_260;
BgL_arg1789z00_260 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1898z00_552;
{ /* work-queue.scm 139 */
obj_t BgL_thunk1576z00_538;
BgL_thunk1576z00_538 = BgL_thunk2z00_6; 
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1578z00_540;
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1896z00_545;
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1586z00_541;
BgL_new1586z00_541 = 
((BgL_z52workzd2queuezd2itemz52_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuezd2itemz52_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1586z00_541), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2)); 
{ /* work-queue.scm 139 */
BgL_objectz00_bglt BgL_auxz00_1151;
BgL_auxz00_1151 = 
(BgL_objectz00_bglt)(BgL_new1586z00_541); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1151, BFALSE); } 
BgL_res1896z00_545 = BgL_new1586z00_541; } 
BgL_new1578z00_540 = BgL_res1896z00_545; } 
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1897z00_551;
{ /* work-queue.scm 139 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1582z00_546;
BgL_new1582z00_546 = BgL_new1578z00_540; 
{ /* work-queue.scm 139 */
obj_t BgL_thunk1580z00_549;BgL_z52workzd2queuezd2itemz52_bglt BgL_next1581z00_550;
BgL_thunk1580z00_549 = BgL_thunk1576z00_538; 
BgL_next1581z00_550 = BgL_arg1789z00_260; 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_546))->BgL_thunkz00) = ((obj_t)BgL_thunk1580z00_549), BUNSPEC); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_546))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_next1581z00_550), BUNSPEC); 
BgL_res1897z00_551 = BgL_new1582z00_546; } } BgL_res1897z00_551; } 
BgL_res1898z00_552 = BgL_new1578z00_540; } } 
BgL_nwiz00_238 = BgL_res1898z00_552; } } 
{ /* work-queue.scm 142 */
obj_t BgL_arg1764z00_239;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1156;
BgL_auxz00_1156 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_5); 
BgL_arg1764z00_239 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1156))->BgL_mutexz00); } 
{ /* work-queue.scm 144 */
obj_t BgL_zc3anonymousza31767ze3z83_772;
BgL_zc3anonymousza31767ze3z83_772 = 
make_fx_procedure(BGl_zc3anonymousza31767ze3z83zzworkzd2queuezd2, 
(int)(((long)0)), 
(int)(((long)3))); 
PROCEDURE_SET(BgL_zc3anonymousza31767ze3z83_772, 
(int)(((long)0)), BgL_queuez00_5); 
PROCEDURE_SET(BgL_zc3anonymousza31767ze3z83_772, 
(int)(((long)1)), BgL_queuez00_5); 
PROCEDURE_SET(BgL_zc3anonymousza31767ze3z83_772, 
(int)(((long)2)), 
(obj_t)(BgL_nwiz00_238)); 
return 
BGl_withzd2lockzd2zz__threadz00(BgL_arg1764z00_239, BgL_zc3anonymousza31767ze3z83_772);} } } } 
}



/* _work-queue-push! */
obj_t BGl__workzd2queuezd2pushz12z12zzworkzd2queuezd2(obj_t BgL_envz00_773, obj_t BgL_queuez00_774, obj_t BgL_thunk2z00_775)
{ AN_OBJECT;
{ /* work-queue.scm 131 */
return 
BGl_workzd2queuezd2pushz12z12zzworkzd2queuezd2(BgL_queuez00_774, BgL_thunk2z00_775);} 
}



/* <anonymous:1767> */
obj_t BGl_zc3anonymousza31767ze3z83zzworkzd2queuezd2(obj_t BgL_envz00_776)
{ AN_OBJECT;
{ /* work-queue.scm 143 */
{ /* work-queue.scm 144 */
obj_t BgL_queuez00_777;obj_t BgL_instance1692z00_778;obj_t BgL_nwiz00_779;
BgL_queuez00_777 = 
PROCEDURE_REF(BgL_envz00_776, 
(int)(((long)0))); 
BgL_instance1692z00_778 = 
PROCEDURE_REF(BgL_envz00_776, 
(int)(((long)1))); 
BgL_nwiz00_779 = 
PROCEDURE_REF(BgL_envz00_776, 
(int)(((long)2))); 
{ 

{ /* work-queue.scm 144 */
bool_t BgL_testz00_1177;
{ /* work-queue.scm 144 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1722z00_556;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1723z00_557;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1178;
BgL_auxz00_1178 = 
(BgL_z52workzd2queuez80_bglt)(BgL_queuez00_777); 
BgL_arg1722z00_556 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1178))->BgL_firstz00); } 
BgL_arg1723z00_557 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
BgL_testz00_1177 = 
(
(obj_t)(BgL_arg1722z00_556)==
(obj_t)(BgL_arg1723z00_557)); } 
if(BgL_testz00_1177)
{ /* work-queue.scm 144 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1187;BgL_z52workzd2queuez80_bglt BgL_auxz00_1185;
BgL_auxz00_1187 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_nwiz00_779); 
BgL_auxz00_1185 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1185))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1187), BUNSPEC); } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1192;BgL_z52workzd2queuez80_bglt BgL_auxz00_1190;
BgL_auxz00_1192 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_nwiz00_779); 
BgL_auxz00_1190 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1190))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1192), BUNSPEC); } }  else 
{ /* work-queue.scm 144 */
{ /* work-queue.scm 149 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1769z00_243;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1195;
BgL_auxz00_1195 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_arg1769z00_243 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1195))->BgL_lastz00); } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1198;
BgL_auxz00_1198 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_nwiz00_779); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_arg1769z00_243))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1198), BUNSPEC); } } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1203;BgL_z52workzd2queuez80_bglt BgL_auxz00_1201;
BgL_auxz00_1203 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_nwiz00_779); 
BgL_auxz00_1201 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1201))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1203), BUNSPEC); } } } 
{ /* work-queue.scm 152 */
bool_t BgL_testz00_1206;
{ /* work-queue.scm 152 */
obj_t BgL_auxz00_1207;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1208;
BgL_auxz00_1208 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_auxz00_1207 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1208))->BgL_idlezd2threadszd2); } 
BgL_testz00_1206 = 
BGl_2ze3ze3zz__r4_numbers_6_5z00(BgL_auxz00_1207, 
BINT(((long)0))); } 
if(BgL_testz00_1206)
{ /* work-queue.scm 153 */
obj_t BgL_arg1772z00_245;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1213;
BgL_auxz00_1213 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_arg1772z00_245 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1213))->BgL_conditionzd2variablezd2); } 
{ /* work-queue.scm 153 */
obj_t BgL_cz00_570;
BgL_cz00_570 = BgL_arg1772z00_245; 
return 
BBOOL(
bgl_condvar_signal(BgL_cz00_570));} }  else 
{ /* work-queue.scm 154 */
bool_t BgL_testz00_1218;
{ /* work-queue.scm 154 */
obj_t BgL_auxz00_1223;obj_t BgL_auxz00_1219;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1224;
BgL_auxz00_1224 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_auxz00_1223 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1224))->BgL_maxzd2threadszd2); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1220;
BgL_auxz00_1220 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_auxz00_1219 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1220))->BgL_currentzd2threadszd2); } 
BgL_testz00_1218 = 
BGl_2zc3zc3zz__r4_numbers_6_5z00(BgL_auxz00_1219, BgL_auxz00_1223); } 
if(BgL_testz00_1218)
{ /* work-queue.scm 154 */
{ /* work-queue.scm 156 */
BgL_pthreadz00_bglt BgL_arg1774z00_247;
BgL_arg1774z00_247 = 
BGl_makezd2pthreadzd2zz__pth_threadz00(
BGl_gensymz00zz__r4_symbols_6_4z00(
CNST_TABLE_REF(((long)2))), 
BGl_makezd2workzd2queuezd2threadzd2thunkz00zzworkzd2queuezd2(BgL_queuez00_777), ((bool_t)0), BUNSPEC, BUNSPEC, 
BGl_z42pthreadzd2nilz90zz__pth_threadz00()); 
BGl_threadzd2startz12zc0zz__threadz00(
(BgL_threadz00_bglt)(BgL_arg1774z00_247), BNIL); } 
{ /* work-queue.scm 158 */
obj_t BgL_arg1780z00_252;
{ /* work-queue.scm 158 */
obj_t BgL_auxz00_1235;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1236;
BgL_auxz00_1236 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
BgL_auxz00_1235 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1236))->BgL_currentzd2threadszd2); } 
BgL_arg1780z00_252 = 
BGl_2zb2zb2zz__r4_numbers_6_5z00(BgL_auxz00_1235, 
BINT(((long)1))); } 
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1241;
BgL_auxz00_1241 = 
(BgL_z52workzd2queuez80_bglt)(BgL_instance1692z00_778); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1241))->BgL_currentzd2threadszd2) = ((obj_t)BgL_arg1780z00_252), BUNSPEC);} } }  else 
{ /* work-queue.scm 154 */
return BFALSE;} } } } } } 
}



/* object-init */
obj_t BGl_objectzd2initzd2zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
{ /* work-queue.scm 36 */
obj_t BgL_arg1791z00_264;obj_t BgL_arg1792z00_265;obj_t BgL_arg1797z00_269;obj_t BgL_arg1798z00_270;
BgL_arg1791z00_264 = 
CNST_TABLE_REF(((long)3)); 
BgL_arg1792z00_265 = BGl_objectz00zz__objectz00; 
{ /* work-queue.scm 36 */
obj_t BgL_arg1799z00_271;obj_t BgL_arg1800z00_272;
{ /* work-queue.scm 36 */
obj_t BgL_arg1803z00_275;obj_t BgL_arg1804z00_276;
BgL_arg1803z00_275 = 
CNST_TABLE_REF(((long)4)); 
BgL_arg1804z00_276 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1799z00_271 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1803z00_275, BGl_z52workzd2queuezd2itemzd2thunkzd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2itemzd2thunkzd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1804z00_276); } 
{ /* work-queue.scm 36 */
obj_t BgL_arg1805z00_277;obj_t BgL_arg1806z00_278;
BgL_arg1805z00_277 = 
CNST_TABLE_REF(((long)5)); 
BgL_arg1806z00_278 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1800z00_272 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1805z00_277, BGl_z52workzd2queuezd2itemzd2nextzd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2itemzd2nextzd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1806z00_278); } 
{ /* work-queue.scm 36 */
obj_t BgL_list1801z00_273;
{ /* work-queue.scm 36 */
obj_t BgL_arg1802z00_274;
BgL_arg1802z00_274 = 
MAKE_PAIR(BgL_arg1800z00_272, BNIL); 
BgL_list1801z00_273 = 
MAKE_PAIR(BgL_arg1799z00_271, BgL_arg1802z00_274); } 
BgL_arg1797z00_269 = BgL_list1801z00_273; } } 
{ /* work-queue.scm 36 */
obj_t BgL_v1702z00_279;
BgL_v1702z00_279 = 
create_vector(
(int)(((long)0))); 
BgL_arg1798z00_270 = BgL_v1702z00_279; } 
BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2 = 
BGl_registerzd2classz12zc0zz__objectz00(BgL_arg1791z00_264, BgL_arg1792z00_265, ((bool_t)0), BGl_makezd2z52workzd2queuezd2itemzd2envz52zzworkzd2queuezd2, BGl_z52allocatezd2z52workzd2queuezd2itemzd2envz00zzworkzd2queuezd2, BGl_z52workzd2queuezd2itemzd2nilzd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2itemzf3zd2envz73zzworkzd2queuezd2, ((long)362361597), BgL_arg1797z00_269, BFALSE, BgL_arg1798z00_270); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1807z00_280;obj_t BgL_arg1808z00_281;obj_t BgL_arg1813z00_285;obj_t BgL_arg1814z00_286;
BgL_arg1807z00_280 = 
CNST_TABLE_REF(((long)6)); 
BgL_arg1808z00_281 = BGl_objectz00zz__objectz00; 
{ /* work-queue.scm 39 */
obj_t BgL_arg1815z00_287;obj_t BgL_arg1816z00_288;obj_t BgL_arg1817z00_289;obj_t BgL_arg1818z00_290;obj_t BgL_arg1819z00_291;obj_t BgL_arg1820z00_292;obj_t BgL_arg1821z00_293;obj_t BgL_arg1822z00_294;
{ /* work-queue.scm 39 */
obj_t BgL_arg1833z00_303;obj_t BgL_arg1834z00_304;
BgL_arg1833z00_303 = 
CNST_TABLE_REF(((long)7)); 
BgL_arg1834z00_304 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1815z00_287 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1833z00_303, BGl_z52workzd2queuezd2maxzd2threadszd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2maxzd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1834z00_304); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1836z00_305;obj_t BgL_arg1837z00_306;
BgL_arg1836z00_305 = 
CNST_TABLE_REF(((long)8)); 
BgL_arg1837z00_306 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1816z00_288 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1836z00_305, BGl_z52workzd2queuezd2idlezd2threadszd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2idlezd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1837z00_306); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1838z00_307;obj_t BgL_arg1839z00_308;
BgL_arg1838z00_307 = 
CNST_TABLE_REF(((long)9)); 
BgL_arg1839z00_308 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1817z00_289 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1838z00_307, BGl_z52workzd2queuezd2currentzd2threadszd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2currentzd2threadszd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1839z00_308); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1840z00_309;obj_t BgL_arg1841z00_310;
BgL_arg1840z00_309 = 
CNST_TABLE_REF(((long)10)); 
BgL_arg1841z00_310 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1818z00_290 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1840z00_309, BGl_z52workzd2queuezd2finishzd2envz80zzworkzd2queuezd2, BGl_z52workzd2queuezd2finishzd2setz12zd2envz40zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1841z00_310); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1842z00_311;obj_t BgL_arg1843z00_312;
BgL_arg1842z00_311 = 
CNST_TABLE_REF(((long)0)); 
BgL_arg1843z00_312 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1819z00_291 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1842z00_311, BGl_z52workzd2queuezd2mutexzd2envz80zzworkzd2queuezd2, BGl_z52workzd2queuezd2mutexzd2setz12zd2envz40zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1843z00_312); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1844z00_313;obj_t BgL_arg1845z00_314;
BgL_arg1844z00_313 = 
CNST_TABLE_REF(((long)1)); 
BgL_arg1845z00_314 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1820z00_292 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1844z00_313, BGl_z52workzd2queuezd2conditionzd2variablezd2envz52zzworkzd2queuezd2, BGl_z52workzd2queuezd2conditionzd2variablezd2setz12zd2envz92zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1845z00_314); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1846z00_315;obj_t BgL_arg1847z00_316;
BgL_arg1846z00_315 = 
CNST_TABLE_REF(((long)11)); 
BgL_arg1847z00_316 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1821z00_293 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1846z00_315, BGl_z52workzd2queuezd2firstzd2envz80zzworkzd2queuezd2, BGl_z52workzd2queuezd2firstzd2setz12zd2envz40zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1847z00_316); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1848z00_317;obj_t BgL_arg1849z00_318;
BgL_arg1848z00_317 = 
CNST_TABLE_REF(((long)12)); 
BgL_arg1849z00_318 = 
BGl_classzd2fieldzd2nozd2defaultzd2valuez00zz__objectz00(); 
BgL_arg1822z00_294 = 
BGl_makezd2classzd2fieldz00zz__objectz00(BgL_arg1848z00_317, BGl_z52workzd2queuezd2lastzd2envz80zzworkzd2queuezd2, BGl_z52workzd2queuezd2lastzd2setz12zd2envz40zzworkzd2queuezd2, BUNSPEC, ((bool_t)0), BFALSE, BgL_arg1849z00_318); } 
{ /* work-queue.scm 39 */
obj_t BgL_list1823z00_295;
{ /* work-queue.scm 39 */
obj_t BgL_arg1824z00_296;
{ /* work-queue.scm 39 */
obj_t BgL_arg1825z00_297;
{ /* work-queue.scm 39 */
obj_t BgL_arg1826z00_298;
{ /* work-queue.scm 39 */
obj_t BgL_arg1827z00_299;
{ /* work-queue.scm 39 */
obj_t BgL_arg1828z00_300;
{ /* work-queue.scm 39 */
obj_t BgL_arg1830z00_301;
{ /* work-queue.scm 39 */
obj_t BgL_arg1831z00_302;
BgL_arg1831z00_302 = 
MAKE_PAIR(BgL_arg1822z00_294, BNIL); 
BgL_arg1830z00_301 = 
MAKE_PAIR(BgL_arg1821z00_293, BgL_arg1831z00_302); } 
BgL_arg1828z00_300 = 
MAKE_PAIR(BgL_arg1820z00_292, BgL_arg1830z00_301); } 
BgL_arg1827z00_299 = 
MAKE_PAIR(BgL_arg1819z00_291, BgL_arg1828z00_300); } 
BgL_arg1826z00_298 = 
MAKE_PAIR(BgL_arg1818z00_290, BgL_arg1827z00_299); } 
BgL_arg1825z00_297 = 
MAKE_PAIR(BgL_arg1817z00_289, BgL_arg1826z00_298); } 
BgL_arg1824z00_296 = 
MAKE_PAIR(BgL_arg1816z00_288, BgL_arg1825z00_297); } 
BgL_list1823z00_295 = 
MAKE_PAIR(BgL_arg1815z00_287, BgL_arg1824z00_296); } 
BgL_arg1813z00_285 = BgL_list1823z00_295; } } 
{ /* work-queue.scm 39 */
obj_t BgL_v1703z00_319;
BgL_v1703z00_319 = 
create_vector(
(int)(((long)0))); 
BgL_arg1814z00_286 = BgL_v1703z00_319; } 
BGl_z52workzd2queuez80zzworkzd2queuezd2 = 
BGl_registerzd2classz12zc0zz__objectz00(BgL_arg1807z00_280, BgL_arg1808z00_281, ((bool_t)0), BGl_makezd2z52workzd2queuezd2envz80zzworkzd2queuezd2, BGl_z52allocatezd2z52workzd2queuezd2envzd2zzworkzd2queuezd2, BGl_z52workzd2queuezd2nilzd2envz80zzworkzd2queuezd2, BGl_z52workzd2queuezf3zd2envza1zzworkzd2queuezd2, ((long)440540374), BgL_arg1813z00_285, BFALSE, BgL_arg1814z00_286); } 
BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2 = BUNSPEC; 
return ( 
BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2 = BUNSPEC, BUNSPEC) ;} 
}



/* _%work-queue? */
obj_t BGl__z52workzd2queuezf3z73zzworkzd2queuezd2(obj_t BgL_envz00_848, obj_t BgL_obj1685z00_849)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
return 
BBOOL(
BGl_iszd2azf3z21zz__objectz00(BgL_obj1685z00_849, BGl_z52workzd2queuez80zzworkzd2queuezd2));} 
}



/* make-%work-queue */
BgL_z52workzd2queuez80_bglt BGl_makezd2z52workzd2queuez52zzworkzd2queuezd2(obj_t BgL_maxzd2threads1622zd2_12, obj_t BgL_idlezd2threads1623zd2_13, obj_t BgL_currentzd2threads1624zd2_14, obj_t BgL_finish1625z00_15, obj_t BgL_mutex1626z00_16, obj_t BgL_conditionzd2variable1627zd2_17, BgL_z52workzd2queuezd2itemz52_bglt BgL_first1628z00_18, BgL_z52workzd2queuezd2itemz52_bglt BgL_last1629z00_19)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1630z00_588;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_res1901z00_593;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1650z00_589;
BgL_new1650z00_589 = 
((BgL_z52workzd2queuez80_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuez80_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1650z00_589), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuez80zzworkzd2queuezd2)); 
{ /* work-queue.scm 39 */
BgL_objectz00_bglt BgL_auxz00_1298;
BgL_auxz00_1298 = 
(BgL_objectz00_bglt)(BgL_new1650z00_589); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1298, BFALSE); } 
BgL_res1901z00_593 = BgL_new1650z00_589; } 
BgL_new1630z00_588 = BgL_res1901z00_593; } 
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_res1902z00_611;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1640z00_594;
BgL_new1640z00_594 = BgL_new1630z00_588; 
{ /* work-queue.scm 39 */
obj_t BgL_maxzd2threads1632zd2_603;obj_t BgL_idlezd2threads1633zd2_604;obj_t BgL_currentzd2threads1634zd2_605;obj_t BgL_finish1635z00_606;obj_t BgL_mutex1636z00_607;obj_t BgL_conditionzd2variable1637zd2_608;BgL_z52workzd2queuezd2itemz52_bglt BgL_first1638z00_609;BgL_z52workzd2queuezd2itemz52_bglt BgL_last1639z00_610;
BgL_maxzd2threads1632zd2_603 = BgL_maxzd2threads1622zd2_12; 
BgL_idlezd2threads1633zd2_604 = BgL_idlezd2threads1623zd2_13; 
BgL_currentzd2threads1634zd2_605 = BgL_currentzd2threads1624zd2_14; 
BgL_finish1635z00_606 = BgL_finish1625z00_15; 
BgL_mutex1636z00_607 = BgL_mutex1626z00_16; 
BgL_conditionzd2variable1637zd2_608 = BgL_conditionzd2variable1627zd2_17; 
BgL_first1638z00_609 = BgL_first1628z00_18; 
BgL_last1639z00_610 = BgL_last1629z00_19; 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_maxzd2threadszd2) = ((obj_t)BgL_maxzd2threads1632zd2_603), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_idlezd2threadszd2) = ((obj_t)BgL_idlezd2threads1633zd2_604), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_currentzd2threadszd2) = ((obj_t)BgL_currentzd2threads1634zd2_605), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_finishz00) = ((obj_t)BgL_finish1635z00_606), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_mutexz00) = ((obj_t)BgL_mutex1636z00_607), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_conditionzd2variablezd2) = ((obj_t)BgL_conditionzd2variable1637zd2_608), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_first1638z00_609), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_594))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_last1639z00_610), BUNSPEC); 
BgL_res1902z00_611 = BgL_new1640z00_594; } } BgL_res1902z00_611; } 
return BgL_new1630z00_588;} } 
}



/* _make-%work-queue */
obj_t BGl__makezd2z52workzd2queuez52zzworkzd2queuezd2(obj_t BgL_envz00_797, obj_t BgL_maxzd2threads1622zd2_798, obj_t BgL_idlezd2threads1623zd2_799, obj_t BgL_currentzd2threads1624zd2_800, obj_t BgL_finish1625z00_801, obj_t BgL_mutex1626z00_802, obj_t BgL_conditionzd2variable1627zd2_803, obj_t BgL_first1628z00_804, obj_t BgL_last1629z00_805)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
return 
(obj_t)(
BGl_makezd2z52workzd2queuez52zzworkzd2queuezd2(BgL_maxzd2threads1622zd2_798, BgL_idlezd2threads1623zd2_799, BgL_currentzd2threads1624zd2_800, BgL_finish1625z00_801, BgL_mutex1626z00_802, BgL_conditionzd2variable1627zd2_803, 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_first1628z00_804), 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_last1629z00_805)));} 
}



/* _%allocate-%work-queue */
obj_t BGl__z52allocatezd2z52workzd2queuez00zzworkzd2queuezd2(obj_t BgL_envz00_806)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_auxz00_1313;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_res1923z00_885;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1650z00_883;
BgL_new1650z00_883 = 
((BgL_z52workzd2queuez80_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuez80_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1650z00_883), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuez80zzworkzd2queuezd2)); 
{ /* work-queue.scm 39 */
BgL_objectz00_bglt BgL_auxz00_1318;
BgL_auxz00_1318 = 
(BgL_objectz00_bglt)(BgL_new1650z00_883); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1318, BFALSE); } 
BgL_res1923z00_885 = BgL_new1650z00_883; } 
BgL_auxz00_1313 = BgL_res1923z00_885; } 
return 
(obj_t)(BgL_auxz00_1313);} } 
}



/* %work-queue-nil */
BgL_z52workzd2queuez80_bglt BGl_z52workzd2queuezd2nilz52zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 39 */
if(
(BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2==BUNSPEC))
{ /* work-queue.scm 39 */
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_res1903z00_628;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1650z00_624;
BgL_new1650z00_624 = 
((BgL_z52workzd2queuez80_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuez80_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1650z00_624), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuez80zzworkzd2queuezd2)); 
{ /* work-queue.scm 39 */
BgL_objectz00_bglt BgL_auxz00_1328;
BgL_auxz00_1328 = 
(BgL_objectz00_bglt)(BgL_new1650z00_624); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1328, BFALSE); } 
BgL_res1903z00_628 = BgL_new1650z00_624; } 
BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2 = 
(obj_t)(BgL_res1903z00_628); } 
{ /* work-queue.scm 39 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1852z00_332;BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1853z00_333;
BgL_arg1852z00_332 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
BgL_arg1853z00_333 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_res1904z00_646;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_new1640z00_629;
BgL_new1640z00_629 = 
(BgL_z52workzd2queuez80_bglt)(BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2); 
{ /* work-queue.scm 39 */
obj_t BgL_maxzd2threads1632zd2_638;obj_t BgL_idlezd2threads1633zd2_639;obj_t BgL_currentzd2threads1634zd2_640;obj_t BgL_finish1635z00_641;obj_t BgL_mutex1636z00_642;obj_t BgL_conditionzd2variable1637zd2_643;BgL_z52workzd2queuezd2itemz52_bglt BgL_first1638z00_644;BgL_z52workzd2queuezd2itemz52_bglt BgL_last1639z00_645;
BgL_maxzd2threads1632zd2_638 = BUNSPEC; 
BgL_idlezd2threads1633zd2_639 = BUNSPEC; 
BgL_currentzd2threads1634zd2_640 = BUNSPEC; 
BgL_finish1635z00_641 = BUNSPEC; 
BgL_mutex1636z00_642 = BUNSPEC; 
BgL_conditionzd2variable1637zd2_643 = BUNSPEC; 
BgL_first1638z00_644 = BgL_arg1852z00_332; 
BgL_last1639z00_645 = BgL_arg1853z00_333; 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_maxzd2threadszd2) = ((obj_t)BgL_maxzd2threads1632zd2_638), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_idlezd2threadszd2) = ((obj_t)BgL_idlezd2threads1633zd2_639), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_currentzd2threadszd2) = ((obj_t)BgL_currentzd2threads1634zd2_640), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_finishz00) = ((obj_t)BgL_finish1635z00_641), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_mutexz00) = ((obj_t)BgL_mutex1636z00_642), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_conditionzd2variablezd2) = ((obj_t)BgL_conditionzd2variable1637zd2_643), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_first1638z00_644), BUNSPEC); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_new1640z00_629))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_last1639z00_645), BUNSPEC); 
BgL_res1904z00_646 = BgL_new1640z00_629; } } 
(obj_t)(BgL_res1904z00_646); } } }  else 
{ /* work-queue.scm 39 */BFALSE; } 
return 
(BgL_z52workzd2queuez80_bglt)(BGl_z52thezd2z52workzd2queuezd2nilzd2zzworkzd2queuezd2);} 
}



/* _%work-queue-nil */
obj_t BGl__z52workzd2queuezd2nilz52zzworkzd2queuezd2(obj_t BgL_envz00_847)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
return 
(obj_t)(
BGl_z52workzd2queuezd2nilz52zzworkzd2queuezd2());} 
}



/* _%work-queue-max-threads-set! */
obj_t BGl__z52workzd2queuezd2maxzd2threadszd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_809, obj_t BgL_obj1600z00_810, obj_t BgL_val1599z00_811)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1347;
BgL_auxz00_1347 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1600z00_810); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1347))->BgL_maxzd2threadszd2) = ((obj_t)BgL_val1599z00_811), BUNSPEC);} } 
}



/* _%work-queue-max-threads */
obj_t BGl__z52workzd2queuezd2maxzd2threadsz80zzworkzd2queuezd2(obj_t BgL_envz00_807, obj_t BgL_obj1598z00_808)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1350;
BgL_auxz00_1350 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1598z00_808); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1350))->BgL_maxzd2threadszd2);} } 
}



/* _%work-queue-idle-threads-set! */
obj_t BGl__z52workzd2queuezd2idlezd2threadszd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_814, obj_t BgL_obj1603z00_815, obj_t BgL_val1602z00_816)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1353;
BgL_auxz00_1353 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1603z00_815); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1353))->BgL_idlezd2threadszd2) = ((obj_t)BgL_val1602z00_816), BUNSPEC);} } 
}



/* _%work-queue-idle-threads */
obj_t BGl__z52workzd2queuezd2idlezd2threadsz80zzworkzd2queuezd2(obj_t BgL_envz00_812, obj_t BgL_obj1601z00_813)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1356;
BgL_auxz00_1356 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1601z00_813); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1356))->BgL_idlezd2threadszd2);} } 
}



/* _%work-queue-current-threads-set! */
obj_t BGl__z52workzd2queuezd2currentzd2threadszd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_819, obj_t BgL_obj1606z00_820, obj_t BgL_val1605z00_821)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1359;
BgL_auxz00_1359 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1606z00_820); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1359))->BgL_currentzd2threadszd2) = ((obj_t)BgL_val1605z00_821), BUNSPEC);} } 
}



/* _%work-queue-current-threads */
obj_t BGl__z52workzd2queuezd2currentzd2threadsz80zzworkzd2queuezd2(obj_t BgL_envz00_817, obj_t BgL_obj1604z00_818)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1362;
BgL_auxz00_1362 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1604z00_818); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1362))->BgL_currentzd2threadszd2);} } 
}



/* _%work-queue-finish-set! */
obj_t BGl__z52workzd2queuezd2finishzd2setz12z92zzworkzd2queuezd2(obj_t BgL_envz00_824, obj_t BgL_obj1609z00_825, obj_t BgL_val1608z00_826)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1365;
BgL_auxz00_1365 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1609z00_825); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1365))->BgL_finishz00) = ((obj_t)BgL_val1608z00_826), BUNSPEC);} } 
}



/* _%work-queue-finish */
obj_t BGl__z52workzd2queuezd2finishz52zzworkzd2queuezd2(obj_t BgL_envz00_822, obj_t BgL_obj1607z00_823)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1368;
BgL_auxz00_1368 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1607z00_823); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1368))->BgL_finishz00);} } 
}



/* _%work-queue-mutex-set! */
obj_t BGl__z52workzd2queuezd2mutexzd2setz12z92zzworkzd2queuezd2(obj_t BgL_envz00_829, obj_t BgL_obj1612z00_830, obj_t BgL_val1611z00_831)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1371;
BgL_auxz00_1371 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1612z00_830); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1371))->BgL_mutexz00) = ((obj_t)BgL_val1611z00_831), BUNSPEC);} } 
}



/* _%work-queue-mutex */
obj_t BGl__z52workzd2queuezd2mutexz52zzworkzd2queuezd2(obj_t BgL_envz00_827, obj_t BgL_obj1610z00_828)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1374;
BgL_auxz00_1374 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1610z00_828); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1374))->BgL_mutexz00);} } 
}



/* _%work-queue-condition-variable-set! */
obj_t BGl__z52workzd2queuezd2conditionzd2variablezd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_834, obj_t BgL_obj1615z00_835, obj_t BgL_val1614z00_836)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1377;
BgL_auxz00_1377 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1615z00_835); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1377))->BgL_conditionzd2variablezd2) = ((obj_t)BgL_val1614z00_836), BUNSPEC);} } 
}



/* _%work-queue-condition-variable */
obj_t BGl__z52workzd2queuezd2conditionzd2variablez80zzworkzd2queuezd2(obj_t BgL_envz00_832, obj_t BgL_obj1613z00_833)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1380;
BgL_auxz00_1380 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1613z00_833); 
return 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1380))->BgL_conditionzd2variablezd2);} } 
}



/* _%work-queue-first-set! */
obj_t BGl__z52workzd2queuezd2firstzd2setz12z92zzworkzd2queuezd2(obj_t BgL_envz00_839, obj_t BgL_obj1618z00_840, obj_t BgL_val1617z00_841)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1385;BgL_z52workzd2queuez80_bglt BgL_auxz00_1383;
BgL_auxz00_1385 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_val1617z00_841); 
BgL_auxz00_1383 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1618z00_840); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1383))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1385), BUNSPEC);} } 
}



/* _%work-queue-first */
obj_t BGl__z52workzd2queuezd2firstz52zzworkzd2queuezd2(obj_t BgL_envz00_837, obj_t BgL_obj1616z00_838)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ /* work-queue.scm 39 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1388;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1389;
BgL_auxz00_1389 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1616z00_838); 
BgL_auxz00_1388 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1389))->BgL_firstz00); } 
return 
(obj_t)(BgL_auxz00_1388);} } 
}



/* _%work-queue-last-set! */
obj_t BGl__z52workzd2queuezd2lastzd2setz12z92zzworkzd2queuezd2(obj_t BgL_envz00_844, obj_t BgL_obj1621z00_845, obj_t BgL_val1620z00_846)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1395;BgL_z52workzd2queuez80_bglt BgL_auxz00_1393;
BgL_auxz00_1395 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_val1620z00_846); 
BgL_auxz00_1393 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1621z00_845); 
return 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1393))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1395), BUNSPEC);} } 
}



/* _%work-queue-last */
obj_t BGl__z52workzd2queuezd2lastz52zzworkzd2queuezd2(obj_t BgL_envz00_842, obj_t BgL_obj1619z00_843)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ /* work-queue.scm 39 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1398;
{ 
BgL_z52workzd2queuez80_bglt BgL_auxz00_1399;
BgL_auxz00_1399 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1619z00_843); 
BgL_auxz00_1398 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_auxz00_1399))->BgL_lastz00); } 
return 
(obj_t)(BgL_auxz00_1398);} } 
}



/* _%work-queue-item? */
obj_t BGl__z52workzd2queuezd2itemzf3za1zzworkzd2queuezd2(obj_t BgL_envz00_795, obj_t BgL_obj1597z00_796)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
return 
BBOOL(
BGl_iszd2azf3z21zz__objectz00(BgL_obj1597z00_796, BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2));} 
}



/* make-%work-queue-item */
BgL_z52workzd2queuezd2itemz52_bglt BGl_makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2(obj_t BgL_thunk1576z00_57, BgL_z52workzd2queuezd2itemz52_bglt BgL_next1577z00_58)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1578z00_647;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1905z00_652;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1586z00_648;
BgL_new1586z00_648 = 
((BgL_z52workzd2queuezd2itemz52_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuezd2itemz52_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1586z00_648), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2)); 
{ /* work-queue.scm 36 */
BgL_objectz00_bglt BgL_auxz00_1409;
BgL_auxz00_1409 = 
(BgL_objectz00_bglt)(BgL_new1586z00_648); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1409, BFALSE); } 
BgL_res1905z00_652 = BgL_new1586z00_648; } 
BgL_new1578z00_647 = BgL_res1905z00_652; } 
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1906z00_658;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1582z00_653;
BgL_new1582z00_653 = BgL_new1578z00_647; 
{ /* work-queue.scm 36 */
obj_t BgL_thunk1580z00_656;BgL_z52workzd2queuezd2itemz52_bglt BgL_next1581z00_657;
BgL_thunk1580z00_656 = BgL_thunk1576z00_57; 
BgL_next1581z00_657 = BgL_next1577z00_58; 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_653))->BgL_thunkz00) = ((obj_t)BgL_thunk1580z00_656), BUNSPEC); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_653))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_next1581z00_657), BUNSPEC); 
BgL_res1906z00_658 = BgL_new1582z00_653; } } BgL_res1906z00_658; } 
return BgL_new1578z00_647;} } 
}



/* _make-%work-queue-item */
obj_t BGl__makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2(obj_t BgL_envz00_780, obj_t BgL_thunk1576z00_781, obj_t BgL_next1577z00_782)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
return 
(obj_t)(
BGl_makezd2z52workzd2queuezd2itemz80zzworkzd2queuezd2(BgL_thunk1576z00_781, 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_next1577z00_782)));} 
}



/* _%allocate-%work-queue-item */
obj_t BGl__z52allocatezd2z52workzd2queuezd2itemzd2zzworkzd2queuezd2(obj_t BgL_envz00_783)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1417;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1924z00_915;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1586z00_913;
BgL_new1586z00_913 = 
((BgL_z52workzd2queuezd2itemz52_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuezd2itemz52_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1586z00_913), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2)); 
{ /* work-queue.scm 36 */
BgL_objectz00_bglt BgL_auxz00_1422;
BgL_auxz00_1422 = 
(BgL_objectz00_bglt)(BgL_new1586z00_913); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1422, BFALSE); } 
BgL_res1924z00_915 = BgL_new1586z00_913; } 
BgL_auxz00_1417 = BgL_res1924z00_915; } 
return 
(obj_t)(BgL_auxz00_1417);} } 
}



/* %work-queue-item-nil */
BgL_z52workzd2queuezd2itemz52_bglt BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 36 */
if(
(BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2==BUNSPEC))
{ /* work-queue.scm 36 */
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1907z00_669;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1586z00_665;
BgL_new1586z00_665 = 
((BgL_z52workzd2queuezd2itemz52_bglt)BREF( GC_MALLOC ( sizeof(struct BgL_z52workzd2queuezd2itemz52_bgl) ))); 
BGL_OBJECT_CLASS_NUM_SET(
(BgL_objectz00_bglt)(BgL_new1586z00_665), 
BGl_classzd2numzd2zz__objectz00(BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2)); 
{ /* work-queue.scm 36 */
BgL_objectz00_bglt BgL_auxz00_1432;
BgL_auxz00_1432 = 
(BgL_objectz00_bglt)(BgL_new1586z00_665); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1432, BFALSE); } 
BgL_res1907z00_669 = BgL_new1586z00_665; } 
BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2 = 
(obj_t)(BgL_res1907z00_669); } 
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1856z00_340;
BgL_arg1856z00_340 = 
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(); 
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_res1908z00_674;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_new1582z00_670;
BgL_new1582z00_670 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2); 
{ /* work-queue.scm 36 */
obj_t BgL_thunk1580z00_672;BgL_z52workzd2queuezd2itemz52_bglt BgL_next1581z00_673;
BgL_thunk1580z00_672 = BGl_conszd2envzd2zz__r4_pairs_and_lists_6_3z00; 
BgL_next1581z00_673 = BgL_arg1856z00_340; 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_670))->BgL_thunkz00) = ((obj_t)BgL_thunk1580z00_672), BUNSPEC); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_new1582z00_670))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_next1581z00_673), BUNSPEC); 
BgL_res1908z00_674 = BgL_new1582z00_670; } } 
(obj_t)(BgL_res1908z00_674); } } }  else 
{ /* work-queue.scm 36 */BFALSE; } 
return 
(BgL_z52workzd2queuezd2itemz52_bglt)(BGl_z52thezd2z52workzd2queuezd2itemzd2nilz00zzworkzd2queuezd2);} 
}



/* _%work-queue-item-nil */
obj_t BGl__z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2(obj_t BgL_envz00_794)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
return 
(obj_t)(
BGl_z52workzd2queuezd2itemzd2nilz80zzworkzd2queuezd2());} 
}



/* _%work-queue-item-thunk-set! */
obj_t BGl__z52workzd2queuezd2itemzd2thunkzd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_786, obj_t BgL_obj1572z00_787, obj_t BgL_val1570z00_788)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1444;
BgL_auxz00_1444 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_obj1572z00_787); 
return 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_auxz00_1444))->BgL_thunkz00) = ((obj_t)BgL_val1570z00_788), BUNSPEC);} } 
}



/* _%work-queue-item-thunk */
obj_t BGl__z52workzd2queuezd2itemzd2thunkz80zzworkzd2queuezd2(obj_t BgL_envz00_784, obj_t BgL_obj1569z00_785)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1447;
BgL_auxz00_1447 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_obj1569z00_785); 
return 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_auxz00_1447))->BgL_thunkz00);} } 
}



/* _%work-queue-item-next-set! */
obj_t BGl__z52workzd2queuezd2itemzd2nextzd2setz12z40zzworkzd2queuezd2(obj_t BgL_envz00_791, obj_t BgL_obj1575z00_792, obj_t BgL_val1574z00_793)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1452;BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1450;
BgL_auxz00_1452 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_val1574z00_793); 
BgL_auxz00_1450 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_obj1575z00_792); 
return 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_auxz00_1450))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1452), BUNSPEC);} } 
}



/* _%work-queue-item-next */
obj_t BGl__z52workzd2queuezd2itemzd2nextz80zzworkzd2queuezd2(obj_t BgL_envz00_789, obj_t BgL_obj1573z00_790)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1455;
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1456;
BgL_auxz00_1456 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_obj1573z00_790); 
BgL_auxz00_1455 = 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_auxz00_1456))->BgL_nextz00); } 
return 
(obj_t)(BgL_auxz00_1455);} } 
}



/* generic-init */
obj_t BGl_genericzd2initzd2zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
return BUNSPEC;} 
}



/* method-init */
obj_t BGl_methodzd2initzd2zzworkzd2queuezd2()
{ AN_OBJECT;
{ /* work-queue.scm 33 */
BGl_addzd2methodz12zc0zz__objectz00(BGl_objectzd2ze3structzd2envze3zz__objectz00, BGl_z52workzd2queuez80zzworkzd2queuezd2, BGl_proc1916z00zzworkzd2queuezd2); 
BGl_addzd2methodz12zc0zz__objectz00(BGl_structzb2objectzd2ze3objectzd2envz51zz__objectz00, BGl_z52workzd2queuez80zzworkzd2queuezd2, BGl_proc1917z00zzworkzd2queuezd2); 
BGl_addzd2methodz12zc0zz__objectz00(BGl_objectzd2ze3structzd2envze3zz__objectz00, BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2, BGl_proc1918z00zzworkzd2queuezd2); 
return 
BGl_addzd2methodz12zc0zz__objectz00(BGl_structzb2objectzd2ze3objectzd2envz51zz__objectz00, BGl_z52workzd2queuezd2itemz52zzworkzd2queuezd2, BGl_proc1919z00zzworkzd2queuezd2);} 
}



/* struct+object->objec1711 */
obj_t BGl_structzb2objectzd2ze3objec1711z83zzworkzd2queuezd2(obj_t BgL_envz00_857, obj_t BgL_oz00_858, obj_t BgL_sz00_859)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_oz00_388;obj_t BgL_sz00_389;
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1464;
BgL_oz00_388 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_oz00_858); 
BgL_sz00_389 = BgL_sz00_859; 
{ /* work-queue.scm 36 */
obj_t BgL_arg1885z00_750;
BgL_arg1885z00_750 = 
STRUCT_REF(BgL_sz00_389, 
(int)(((long)0))); 
{ /* work-queue.scm 36 */
BgL_objectz00_bglt BgL_auxz00_1467;
BgL_auxz00_1467 = 
(BgL_objectz00_bglt)(BgL_oz00_388); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1467, BgL_arg1885z00_750); } } 
{ 
obj_t BgL_auxz00_1470;
BgL_auxz00_1470 = 
STRUCT_REF(BgL_sz00_389, 
(int)(((long)1))); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_oz00_388))->BgL_thunkz00) = ((obj_t)BgL_auxz00_1470), BUNSPEC); } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1474;
BgL_auxz00_1474 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(
STRUCT_REF(BgL_sz00_389, 
(int)(((long)2)))); 
((((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_oz00_388))->BgL_nextz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1474), BUNSPEC); } 
BgL_auxz00_1464 = BgL_oz00_388; 
return 
(obj_t)(BgL_auxz00_1464);} } } 
}



/* object->struct-%work1709 */
obj_t BGl_objectzd2ze3structzd2z52work1709zb1zzworkzd2queuezd2(obj_t BgL_envz00_860, obj_t BgL_obj1587z00_861)
{ AN_OBJECT;
{ /* work-queue.scm 36 */
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_obj1587z00_378;
BgL_obj1587z00_378 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(BgL_obj1587z00_861); 
{ /* work-queue.scm 36 */
obj_t BgL_res1588z00_731;
{ /* work-queue.scm 36 */
obj_t BgL_keyz00_736;
BgL_keyz00_736 = 
CNST_TABLE_REF(((long)3)); 
BgL_res1588z00_731 = 
make_struct(BgL_keyz00_736, 
(int)(((long)3)), BUNSPEC); } 
{ /* work-queue.scm 36 */
int BgL_auxz00_1484;
BgL_auxz00_1484 = 
(int)(((long)0)); 
STRUCT_SET(BgL_res1588z00_731, BgL_auxz00_1484, BFALSE); } 
{ /* work-queue.scm 36 */
obj_t BgL_arg1881z00_733;
BgL_arg1881z00_733 = 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_obj1587z00_378))->BgL_thunkz00); 
{ /* work-queue.scm 36 */
int BgL_auxz00_1488;
BgL_auxz00_1488 = 
(int)(((long)1)); 
STRUCT_SET(BgL_res1588z00_731, BgL_auxz00_1488, BgL_arg1881z00_733); } } 
{ /* work-queue.scm 36 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1883z00_735;
BgL_arg1883z00_735 = 
(((BgL_z52workzd2queuezd2itemz52_bglt)CREF(BgL_obj1587z00_378))->BgL_nextz00); 
{ /* work-queue.scm 36 */
obj_t BgL_auxz00_1494;int BgL_auxz00_1492;
BgL_auxz00_1494 = 
(obj_t)(BgL_arg1883z00_735); 
BgL_auxz00_1492 = 
(int)(((long)2)); 
STRUCT_SET(BgL_res1588z00_731, BgL_auxz00_1492, BgL_auxz00_1494); } } 
return BgL_res1588z00_731;} } } 
}



/* struct+object->objec1707 */
obj_t BGl_structzb2objectzd2ze3objec1707z83zzworkzd2queuezd2(obj_t BgL_envz00_862, obj_t BgL_oz00_863, obj_t BgL_sz00_864)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_oz00_363;obj_t BgL_sz00_364;
{ /* work-queue.scm 39 */
BgL_z52workzd2queuez80_bglt BgL_auxz00_1498;
BgL_oz00_363 = 
(BgL_z52workzd2queuez80_bglt)(BgL_oz00_863); 
BgL_sz00_364 = BgL_sz00_864; 
{ /* work-queue.scm 39 */
obj_t BgL_arg1876z00_367;
BgL_arg1876z00_367 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)0))); 
{ /* work-queue.scm 39 */
BgL_objectz00_bglt BgL_auxz00_1501;
BgL_auxz00_1501 = 
(BgL_objectz00_bglt)(BgL_oz00_363); 
BGL_OBJECT_WIDENING_SET(BgL_auxz00_1501, BgL_arg1876z00_367); } } 
{ 
obj_t BgL_auxz00_1504;
BgL_auxz00_1504 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)1))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_maxzd2threadszd2) = ((obj_t)BgL_auxz00_1504), BUNSPEC); } 
{ 
obj_t BgL_auxz00_1508;
BgL_auxz00_1508 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)2))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_idlezd2threadszd2) = ((obj_t)BgL_auxz00_1508), BUNSPEC); } 
{ 
obj_t BgL_auxz00_1512;
BgL_auxz00_1512 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)3))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_currentzd2threadszd2) = ((obj_t)BgL_auxz00_1512), BUNSPEC); } 
{ 
obj_t BgL_auxz00_1516;
BgL_auxz00_1516 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)4))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_finishz00) = ((obj_t)BgL_auxz00_1516), BUNSPEC); } 
{ 
obj_t BgL_auxz00_1520;
BgL_auxz00_1520 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)5))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_mutexz00) = ((obj_t)BgL_auxz00_1520), BUNSPEC); } 
{ 
obj_t BgL_auxz00_1524;
BgL_auxz00_1524 = 
STRUCT_REF(BgL_sz00_364, 
(int)(((long)6))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_conditionzd2variablezd2) = ((obj_t)BgL_auxz00_1524), BUNSPEC); } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1528;
BgL_auxz00_1528 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(
STRUCT_REF(BgL_sz00_364, 
(int)(((long)7)))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_firstz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1528), BUNSPEC); } 
{ 
BgL_z52workzd2queuezd2itemz52_bglt BgL_auxz00_1533;
BgL_auxz00_1533 = 
(BgL_z52workzd2queuezd2itemz52_bglt)(
STRUCT_REF(BgL_sz00_364, 
(int)(((long)8)))); 
((((BgL_z52workzd2queuez80_bglt)CREF(BgL_oz00_363))->BgL_lastz00) = ((BgL_z52workzd2queuezd2itemz52_bglt)BgL_auxz00_1533), BUNSPEC); } 
BgL_auxz00_1498 = BgL_oz00_363; 
return 
(obj_t)(BgL_auxz00_1498);} } } 
}



/* object->struct-%work1705 */
obj_t BGl_objectzd2ze3structzd2z52work1705zb1zzworkzd2queuezd2(obj_t BgL_envz00_865, obj_t BgL_obj1651z00_866)
{ AN_OBJECT;
{ /* work-queue.scm 39 */
{ 
BgL_z52workzd2queuez80_bglt BgL_obj1651z00_341;
BgL_obj1651z00_341 = 
(BgL_z52workzd2queuez80_bglt)(BgL_obj1651z00_866); 
{ /* work-queue.scm 39 */
obj_t BgL_res1652z00_344;
{ /* work-queue.scm 39 */
obj_t BgL_keyz00_675;
BgL_keyz00_675 = 
CNST_TABLE_REF(((long)6)); 
BgL_res1652z00_344 = 
make_struct(BgL_keyz00_675, 
(int)(((long)9)), BUNSPEC); } 
{ /* work-queue.scm 39 */
int BgL_auxz00_1543;
BgL_auxz00_1543 = 
(int)(((long)0)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1543, BFALSE); } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1858z00_346;
BgL_arg1858z00_346 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_maxzd2threadszd2); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1547;
BgL_auxz00_1547 = 
(int)(((long)1)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1547, BgL_arg1858z00_346); } } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1860z00_348;
BgL_arg1860z00_348 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_idlezd2threadszd2); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1551;
BgL_auxz00_1551 = 
(int)(((long)2)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1551, BgL_arg1860z00_348); } } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1862z00_350;
BgL_arg1862z00_350 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_currentzd2threadszd2); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1555;
BgL_auxz00_1555 = 
(int)(((long)3)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1555, BgL_arg1862z00_350); } } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1864z00_352;
BgL_arg1864z00_352 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_finishz00); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1559;
BgL_auxz00_1559 = 
(int)(((long)4)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1559, BgL_arg1864z00_352); } } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1866z00_354;
BgL_arg1866z00_354 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_mutexz00); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1563;
BgL_auxz00_1563 = 
(int)(((long)5)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1563, BgL_arg1866z00_354); } } 
{ /* work-queue.scm 39 */
obj_t BgL_arg1868z00_356;
BgL_arg1868z00_356 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_conditionzd2variablezd2); 
{ /* work-queue.scm 39 */
int BgL_auxz00_1567;
BgL_auxz00_1567 = 
(int)(((long)6)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1567, BgL_arg1868z00_356); } } 
{ /* work-queue.scm 39 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1870z00_358;
BgL_arg1870z00_358 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_firstz00); 
{ /* work-queue.scm 39 */
obj_t BgL_auxz00_1573;int BgL_auxz00_1571;
BgL_auxz00_1573 = 
(obj_t)(BgL_arg1870z00_358); 
BgL_auxz00_1571 = 
(int)(((long)7)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1571, BgL_auxz00_1573); } } 
{ /* work-queue.scm 39 */
BgL_z52workzd2queuezd2itemz52_bglt BgL_arg1874z00_360;
BgL_arg1874z00_360 = 
(((BgL_z52workzd2queuez80_bglt)CREF(BgL_obj1651z00_341))->BgL_lastz00); 
{ /* work-queue.scm 39 */
obj_t BgL_auxz00_1579;int BgL_auxz00_1577;
BgL_auxz00_1579 = 
(obj_t)(BgL_arg1874z00_360); 
BgL_auxz00_1577 = 
(int)(((long)8)); 
STRUCT_SET(BgL_res1652z00_344, BgL_auxz00_1577, BgL_auxz00_1579); } } 
return BgL_res1652z00_344;} } } 
}

#ifdef __cplusplus
}
#endif
