//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//    I BBMMBB      BBMMBBI     BBI EEMMFFI BBMMI     BBI EEMMFFI BBMMI       BBMMBBI   EEMMI EEMMLL        //
//    EEI   EEFF  EEI   LLBB  EEMMBBI I BBEE  I EE  EEMMBBI I BBEE  I EE    EEI   LLBB    EEBBI I BB        //
//  I FF        I EE      BBI   EEI     EEI   I EE    EEI     EEI   I EE  I EE      BBI   EEI   I EE        //
//  LLFF        LLEE      EELL  EEI     EEI   I EE    EEI     EEI   I EE  LLEE      EELL  EEI   I EE        //
//  I EE      I I BB      EEI   EEI     EEI   I EE    EEI     EEI   I EE  I BB      EEI   EEI   I EE        //
//    BBLL  I I   BBFF  I EE    EEI     EEI   I BB    EEI     EEI   I BB    BBFF  I EE    BBI   I EE        //
//    I BBMMEE    I BBMMBB    EEMMMMLLBBMMBBLLMMMMEEEEMMMMLLBBMMBBLLMMMMEE  I BBMMBB    EEMMMMLLBBMMBB      //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
//                                                Scott System                                              //
//                                                                                                          //
//                               (c) Copyright 2006-2007, Scottyu China                                     //
//                                                                                                          //
//                                           All Rights Reserved                                            //
//                                                                                                          //
// File    : list.cpp                                                                                       //
// By      : scottyu                                                                                        //
// Version : V1.00                                                                                          //
// Time    : 2008-05-16 9:08:24                                                                             //
//         : 通用的单向链表数据结构处理模块                                                                 //
//----------------------------------------------------------------------------------------------------------//
//                                                                                                          //
// HISTORY                                                                                                  //
//                                                                                                          //
// 1 2008-05-16 9:08:24                                                                                     //
//                                                                                                          //
//                                                                                                          //
//                                                                                                          //
//----------------------------------------------------------------------------------------------------------//

#ifndef __COMMON__LIST___C______
#define __COMMON__LIST___C______	1

#include "list.h"


//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
List * CreateList()
{
	List * list = NULL;
	list = (List *) malloc(sizeof(List));
	if (!list)
		return NULL;
	
	memset(list, 0, sizeof(List));
	
	//----------------------------------------------------------
	//
	//----------------------------------------------------------
	list->Init       = _List_Init;
	list->Free       = _List_Free;
	list->AddTail    = _List_AddTail;
	list->IsEmpty    = _List_IsEmpty;
	list->RemoveHead = _List_RemoveHead;
	list->GetCount   = _List_GetCount;
	list->Print      = _List_Print;
	
	
	//----------------------------------------------------------
	//
	//----------------------------------------------------------
	if (!list->IsInitial)
	{
		list->Init(list);
	}

	return list;
	
}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
void DestroyList(List * list)
{
	if (!list)
		return;

	list->Free(list);

	memset(list, 0, sizeof(List));
	free(list);

	return;
}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static void _List_Init      (List * list )
{
	if (!list)
		return ;

	//----------------------------------------------------------
	// Set both the head and tail pointers to null
	//----------------------------------------------------------
    list->pHead = NULL;
    list->pTail = NULL;
    
    //----------------------------------------------------------
    // Set the node count to zero, since the list is currently empty
    //----------------------------------------------------------
    list->iNodeCount = 0;

	list->IsInitial = TRUE;
}


//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static void _List_Free      (List * list )
{
	//----------------------------------------------------------
	// If the list is empty, exit
	//----------------------------------------------------------
	if ( ! list )
		return;

	//----------------------------------------------------------
    // If the list is not empty, free each node
    //----------------------------------------------------------
    if ( list->iNodeCount )
    {
    	//----------------------------------------------------------
        // Create a pointer to hold each current node and the next node
        //----------------------------------------------------------
        Node * pCurrNode, * pNextNode;

		//----------------------------------------------------------
        // Set the current node to the head of the list
        //----------------------------------------------------------
        pCurrNode = list->pHead;

	
		//----------------------------------------------------------
        // Traverse the list
        //----------------------------------------------------------
        while ( TRUE )
        {
        	//----------------------------------------------------------
        	// Save the pointer to the next node before freeing the current one
        	//----------------------------------------------------------
            pNextNode = pCurrNode->pNext;
            
            //----------------------------------------------------------
            // Clear the current node's data
            //----------------------------------------------------------
            if ( pCurrNode->pData )
				free ( pCurrNode->pData );
				
			//----------------------------------------------------------
            // Clear the node itself
            //----------------------------------------------------------
            if ( pCurrNode )
				free ( pCurrNode );
				
			//----------------------------------------------------------
            // Move to the next node if it exists; otherwise, exit the loop
            //----------------------------------------------------------
            if ( pNextNode )
				pCurrNode = pNextNode;
			else
				break;
        }

		//----------------------------------------------------------
		//
		//----------------------------------------------------------
		list->iNodeCount = 0;
    }
}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static int  _List_AddTail   (List * list, void * pData )
{
	
	//----------------------------------------------------------
	// Create a new node
	//----------------------------------------------------------
    Node * pNewNode = ( Node * ) malloc ( sizeof ( Node ) );
    
    //----------------------------------------------------------
    // Set the node's data to the specified pointer
    //----------------------------------------------------------
    pNewNode->pData = pData;
    
    //----------------------------------------------------------
    // Set the next pointer to NULL, since nothing will lie beyond it
    //----------------------------------------------------------
    pNewNode->pNext = NULL;
    
    //----------------------------------------------------------
    // If the list is currently empty, set both the head and tail pointers to the new node
    //----------------------------------------------------------
    if ( ! list->iNodeCount )
    {
    	
    	//----------------------------------------------------------
        // Point the head and tail of the list at the node
        //----------------------------------------------------------
        list->pHead = pNewNode;
        list->pTail = pNewNode;
        
//		printf("enter empty list \n");
    }
    //----------------------------------------------------------
    // Otherwise append it to the list and update the tail pointer
    //----------------------------------------------------------
    else
    {
    	
    	//----------------------------------------------------------
        // Alter the tail's next pointer to point to the new node
        //----------------------------------------------------------
        list->pTail->pNext = pNewNode;
        
        //----------------------------------------------------------
        // Update the list's tail pointer
        //----------------------------------------------------------
        list->pTail = pNewNode;
        
        
//		printf("enter  list tail \n");
    }
    
    //----------------------------------------------------------
    // Increment the node count
    //----------------------------------------------------------
    list->iNodeCount++;
    
    //----------------------------------------------------------
    // Return the new size of the linked list - 1, which is the node's index
    //----------------------------------------------------------
    return list->iNodeCount - 1;
}


//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static u32 _List_IsEmpty   (List * list)
{
	if (list->iNodeCount == 0)
		return OK;
	else
		return __LINE__;
}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static Node*_List_RemoveHead(List * list)
{
	Node * pNode = NULL;
	if (OK  == _List_IsEmpty(list))
		return NULL;

	//----------------------------------------------------------
	//
	//----------------------------------------------------------
	pNode = list->pHead;
	list->pHead = pNode->pNext;
	list->iNodeCount--;

//	printf("RemoveHead data=%s\n", pNode->pData);

	return pNode;

}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static int  _List_GetCount  (List * list)
{
	if (!list)
		return 0;

	if (OK == _List_IsEmpty(list))
		return 0;

	
	return list->iNodeCount;

}

//------------------------------------------------------------------------------------------------------------
//
// 函数说明
//     
//
// 参数说明
//     无
//
// 返回值
//     无
//
// 其他
//     无
//
//------------------------------------------------------------------------------------------------------------
static void _List_Print     (List * list)
{
	Node * pNode = NULL;
	if (!list)
		return;

	//----------------------------------------------------------
	//
	//----------------------------------------------------------
	pNode = list->pHead;
	
	
	printf("---------------------------------------------------%d\n", list->iNodeCount);
	
	//----------------------------------------------------------
	//
	//----------------------------------------------------------
	while (pNode)
	{
		printf("%s\n", (s8 *)pNode->pData);
		pNode = pNode->pNext;
	}
	
	printf("---------------------------------------------------\n");
}

//------------------------------------------------------------------------------------------------------------
// THE END !
//------------------------------------------------------------------------------------------------------------	
#endif //__COMMON__LIST___C______
	