/*
\file		handle.h
\brief		.
 ----history----
\author     dakota
\date       2007-05-27
\version    0.01
\desc       create

$Author: chengzhiyong $
$Id: handle.h,v 1.1.1.1 2007-11-25 15:09:11 chengzhiyong Exp $
*/
#if !defined(__handle_h__)
#define  __handle_h__

#if defined(__cplusplus)
extern "C" {
#endif

#define HANDLE_SPARE_BIT    8
#define HANDLE_DIFF_BIT     8
#define HANDLE_ENTRY_BIT    8
#define HANDLE_PAGE_BIT     ( 32 - HANDLE_SPARE_BIT - HANDLE_DIFF_BIT - HANDLE_ENTRY_BIT )

#define HANDLE_SPARE_SHIFT  ( HANDLE_DIFF_BIT + HANDLE_ENTRY_BIT + HANDLE_PAGE_BIT )
#define HANDLE_DIFF_SHIFT  ( HANDLE_ENTRY_BIT + HANDLE_PAGE_BIT )
#define HANDLE_ENTRY_SHIFT  ( HANDLE_PAGE_BIT )
#define HANDLE_PAGE_SHIFT  ( 0 )

#define HANDLE_SPARE_MASK   ( ( 1 << HANDLE_SPARE_BIT ) - 1 )
#define HANDLE_DIFF_MASK   ( ( 1 << HANDLE_DIFF_BIT ) - 1 )
#define HANDLE_ENTRY_MASK   ( ( 1 << HANDLE_ENTRY_BIT ) - 1 )
#define HANDLE_PAGE_MASK   ( ( 1 << HANDLE_PAGE_BIT ) - 1 )

#define MAX_PAGE_IN_TBL     ( 1 << HANDLE_PAGE_BIT )
#define MAX_ENTRY_IN_PAGE  ( 1 << HANDLE_ENTRY_BIT )
#define MAX_DIFF_IN_ENTRY   ( ( 1 << HANDLE_DIFF_BIT ) - 1 )

#define VALVE_FREE_ENTRY    ( MAX_ENTRY_IN_PAGE / 10 )
#define NULL_HANDLE         ((int)0)

typedef int HANDLE_ID;

typedef struct tag_ST_HANDLE_ENTRY
{
    void                *pObj;                  /* ��HANDLEӳ��Ķ����ַ */
    char                ucUsedFlag;             /* �Ƿ��Ѿ�ʹ�� */
    HANDLE_ID           handle;                 /* ��ENTRY��Ӧ��HANDLE�����ڵ��� */
    struct tag_ST_HANDLE_ENTRY  *pstNextEntry;  /* ��һ��ENTRY����Ҫ���ڽ����е�ENTRY������ */
    long                dwDiff;                 /* ��ţ���������HANDLE�Ƿ���Ч */
}ST_HANDLE_ENTRY;

typedef struct tag_ST_HANDLE_PAGE
{
    ST_HANDLE_ENTRY         astHandleEntry[MAX_ENTRY_IN_PAGE];    /* ��ҳ��HANDLE���� */
    ST_HANDLE_ENTRY         *pstFirstUnusedEntry;     /* ��һ��û�з����ȥ��ENTRY */
    ST_HANDLE_ENTRY         *pstLastUnusedEntry;     /* ���һ��û�з����ȥ��ENTRY */
    long                    dwEntry_used;           /* �Ѿ������ENTRY�� */
}ST_HANDLE_PAGE;


typedef struct
{
    ST_HANDLE_PAGE          *apstPage[MAX_PAGE_IN_TBL]; /* ���ڿհ�PAGE��ָ����һ������PAGE�������Ѿ������PAGE��ָ��PAGE */      
    long                    entry_free;             /* ��ǰ�ɷ����ENTRY�� */
    ST_HANDLE_PAGE          **ppstCurrentPage;      /* ��ǰ���ڷ���ENTRY��PAGE */
    ST_HANDLE_PAGE          **ppstFirstBlankPage;  /* ��һ���հ�PAGE */
}ST_HANDLE_TABLE;

extern ST_HANDLE_PAGE ** Handle_AllocatePage( ST_HANDLE_TABLE *pstHandleTbl );
extern long Handle_Create( ST_HANDLE_TABLE *pstHandleTbl, void *pObj );
extern void * Handle_Validate( ST_HANDLE_TABLE *pstHandleTbl, long handle );
extern long Handle_Destroy( ST_HANDLE_TABLE *pstHandleTbl, long handle );
extern void Handle_DestroyPage( ST_HANDLE_TABLE *pstHandleTbl, ST_HANDLE_PAGE **ppstPage );

extern ST_HANDLE_PAGE **Handle_FindNextPage( ST_HANDLE_TABLE *pstHandleTbl );

#if defined(__cplusplus)
}
#endif

#endif /* !defined(__handle_h__) */



