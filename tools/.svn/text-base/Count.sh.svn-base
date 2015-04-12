#!/bin/bash
#统计Dzs中补送物品的数量

ToDay=`date  +%Y-%m-%d`
YesterDay=`date -d "-1 day" +%Y-%m-%d`

rm -rf ./Items.text

#发送邮件
SendMail()
{
	mailTo=$1
	mailTitle=$2
	mailText=$3

	/usr/local/games/sapws/script/mail/sendmail.pl -r "$mailTo" -s "$mailTitle" -n "$mailText" 
	
	#echo /usr/local/games/sapws/script/mail/sendmail.pl -r \"$mailTo\" -s \"$mailTitle\" -n \"$mailText\"  >> ./AutoClearRoleCount.log
	if [ $? -ne 0 ]
	then
		echo "发送邮件失败" >> ./logs/CountInfo.log
	else
		echo "发送邮件成功" >> ./logs/CountInfo.log
	fi
}

#echo $ToDay
#echo $YesterDay

mysql -h172.16.176.6 -usap -psap_oss_da OssAutoRob_229 -N -e "select a.iItem_Id,if(a.iItem_Name='', "NULL", a.iItem_Name) as iItem_Name, sum(a.iItem_Num) as Total from tbICSItemTrace a,tbICSComplaint b where a.iTraceHand=-1 and a.iSendResult in (53) and a.iICSId=b.iICSId and b.dtBookTime between '$YesterDay' and '$ToDay' and b.iICSAnaylseStep=5 and b.iICSAnaylseResult=52 and b.iICSAnaylseStat=51 group by a.iItem_Id order by Total desc,a.iItem_Id asc;" > ./data/${ToDay}_Items.txt

MailTo="v_qdpeng;windysong;vitaszhang;chirscheng;hisenwang;shawnluo;maggiesun;andyche;olinayan;v_flwu;v_sjwang;v_wxywu;v_lczhu;v_htaohe;jeromequ"
MailTitle="${YesterDay}_${ToDay}Dzs中补送物品的数量统计"
MailText=`cat ./data/${ToDay}_Items.txt`

SendMail $MailTo $MailTitle "$MailText"
