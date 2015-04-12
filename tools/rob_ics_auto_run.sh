#!/bin/bash
source rob.sh.marcos
ROB_SERVICE_LIB_PATH=/usr/local/games/robgame/bin/${ROB_SERVICE_NAME}/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${ROB_SERVICE_LIB_PATH}
usage(){
	echo "-------------Welcome To RobSystem------------"
	echo ""
	echo "**********************************************"
	echo "Usage"
	echo "**********************************************"
	echo ""
	echo "用法："
	echo "$0 -1 dnf2"
	echo "$0 -程序模块 业务简称"
	echo "例如：eg."
	echo "$0 -1 ${ROB_SERVICE_NAME}"
	echo "表示的意思是，执行${ROB_SERVICE_NAME}业务的第一个过滤模块"
}
robFliterModel(){
	echo "[INFO]: robFliterModel() RUNNINGIX------"
	./rob_core_fliter
	if [ $? -ne 0 ];then
		echo "[ERROR] ./rob_core_fliter Not Exit 0,It is [${?}]" 
		exit $? 
	fi
	proc_time=`date +%s`
	proc_time=`expr $proc_time - $START_TIME`
	echo "[INFO] ./rob_core_fliter Expire ${proc_time}"
}
robRobSlotModel(){
	echo "[INFO]:robRobSlotModel() RUNNING--- ---"
	./rob_core_loginlogout
	if [ $? -ne 0 ];then
		echo "[ERROR] ./rob_core_loginlogout Not Return 0,It is [${?}]"
		exit $?	
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_loginlogout Expire ${proc_time}"
}
robItemFlowModel(){
	echo "[INFO]:robItemFlowModel() RUNNING--- ---"
	./rob_core_item_flow
	if [ $? -ne 0 ];then
		echo "[ERROR] .rob_core_item_flow Not Return 0,It is [${?}]"
		exit $?
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_item_flow Expire ${proc_time}"

}
robItemTraceModel(){
	echo "[INFO]:robItemTraceModel() RUNNING--- ---"
	./rob_core_item_trace
	if [ $? -ne 0 ];then
		echo "[ERROR] .rob_core_item_trace Not Return 0,It is [${?}]"
		exit $?
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_item_trace Expire ${proc_time}"

}
robItemSendModel(){
	echo "[INFO]:robItemSendModel() RUNNING--- ---"
	./rob_core_item_send
	if [ $? -ne 0 ];then
		echo "[ERROR] .rob_core_item_send Not Return 0,It is [${?}]"
		exit $?
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_item_send Expire ${proc_time}"

}
robItemReplyModel(){
	echo "[INFO]:robItemReplyModel() RUNNING--- ---"
	./rob_core_reply_auto
	if [ $? -ne 0 ];then
		echo "[ERROR] .rob_core_reply_auto Not Return 0,It is [${?}]"
		exit $?
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_reply_auto Expire ${proc_time}"

}

robItemRehandleModel(){
	echo "[INFO]:robItemRehandleModel() RUNNING--- ---"
	./rob_core_item_rehandle
	if [ $? -ne 0 ];then
		echo "[ERROR] .rob_core_item_rehandle Not Return 0,It is [${?}]"
		exit $?
	fi
        proc_time=`date +%s`
        proc_time=`expr $proc_time - $START_TIME`
        echo "[INFO] ./rob_core_item_rehandle Expire ${proc_time}"

}
RUN_TYPE=$1
RUN_SERVICE=$2
START_TIME=`date +%s`

if [ $# -ne 2 -o "${RUN_SERVICE}" != "${ROB_SERVICE_NAME}" ];then
	echo "[ERROR] Params Nums Is Must 2, Or Your Service Name Must '${ROB_SERVICE_NAME}'"
	exit -1
fi
case ${RUN_TYPE} in

-1)
	robFliterModel
	;;
-2)
	robRobSlotModel
	;;
-3)
	robItemFlowModel
	;;
-4)
	robItemTraceModel
	;;
-5)
	robItemSendModel
	;;	
-6)
	robItemReplyModel
	;;
-7)
	robItemRehandleModel
	;;
*)
	echo "[ERROR]: Wrong Type Of Running"
	;;
 	
esac
