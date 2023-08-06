/****************************************************************************************
* ALI SAHBAZ
*
* ASOS Framework - "Ali Sahbaz Operating System"
*
* "Stade Machine Design Pattern"
*
* Description: it is a GPOS memory controller ,
*
* Date          : 06.08.2023
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#include <stdio.h>
#include <windows.h>

#include "asos_stade_machine.h"


#define STADES_MAX_COUNT   3

typedef enum {
    IDLE_TASK = ASOS_SM_IDLE_STADE_CASE_ID,
    TEST_STEP_1,
    TEST_STEP_2,
    TEST_STEP_3
}_sm_stade_ids;


/** test application object **/
typedef struct {
     
    asos_stade_machine_t  sm;

    asos_stade_t stades[STADES_MAX_COUNT];
     
}sm_t;


 

static asos_sm_stade_id_type _idle_task_step(asos_stade_machine_t* const sm)
{
    sm_t* me = ASOS_CONTAINER_OF(sm, sm_t, sm);

    printf("idle task run \n");

    asos_stade_machine_set_delay(sm, 10);

    return TEST_STEP_1;
}

static asos_sm_stade_id_type _task_step_1(asos_stade_machine_t* const sm)
{
    sm_t* me = ASOS_CONTAINER_OF(sm, sm_t, sm);

    printf(" task 1 run \n");

    asos_stade_machine_set_delay(sm, 10);

    return TEST_STEP_2;
}

static asos_sm_stade_id_type _task_step_2(asos_stade_machine_t* const sm)
{
    sm_t* me = ASOS_CONTAINER_OF(sm, sm_t, sm);

    printf(" task 2 run \n");

    asos_stade_machine_set_delay(sm, 30);

    return TEST_STEP_3;
}

static asos_sm_stade_id_type _task_step_3(asos_stade_machine_t* const sm)
{
    sm_t* me = ASOS_CONTAINER_OF(sm, sm_t, sm);

    printf(" task 3 run \n");

    asos_stade_machine_set_delay(sm, 30);

    return IDLE_TASK;
}



static void sm_create(sm_t* me )
{  
    asos_stade_machine_create(&me->sm, &_idle_task_step);

    /** stade machine table ***/
    ASOS_STADE_MACHINE_TABLE_ADD(&me->sm, &me->stades[0], TEST_STEP_1, &_task_step_1);
    ASOS_STADE_MACHINE_TABLE_ADD(&me->sm, &me->stades[1], TEST_STEP_2, &_task_step_2);
    ASOS_STADE_MACHINE_TABLE_ADD(&me->sm, &me->stades[2], TEST_STEP_3, &_task_step_3);

}

static void sm_process(sm_t* me)
{ 
    asos_stade_machine_run(&me->sm);
}
















int main() {

    printf("ASOS SM : test starting ... \n\n");
     
    /** super test object **/
    sm_t sm_test;

    sm_create(&sm_test);

    while (1) {
    
        sm_process(&sm_test);
         
        asos_stade_machine_timer_ms(&sm_test.sm);

        Sleep(1);
    }

    return 0;
}