/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018-2019 w4123���, ����
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this
 * program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "CQLogger.h"
#include "GlobalVar.h"
#include <map>

bool Enabled = false;

bool msgSendThreadRunning = false;

CQ::logger DiceLogger("Dice!");

/*
 * �汾��Ϣ
 * �����޸�Dice_Build, Dice_Ver_Without_Build��DiceRequestHeader�Լ�Dice_Ver����
 * ���޸�Dice_Short_Ver��Dice_Full_Ver�����Դﵽ�汾�Զ���
 */
const unsigned short Dice_Build = 509;
const std::string Dice_Ver_Without_Build = "2.3.6";
const std::string DiceRequestHeader = "Dice/" + Dice_Ver_Without_Build;
const std::string Dice_Ver = Dice_Ver_Without_Build + "(" + std::to_string(Dice_Build) + ")";
const std::string Dice_Short_Ver = "Dice! by ���,���� Version " + Dice_Ver;
const std::string Dice_Full_Ver = Dice_Short_Ver + " [MSVC " + std::to_string(_MSC_FULL_VER) + " " + __DATE__ + " " + __TIME__ + "]";
//GlobalMsg["strGetCardCatMessage"]
std::map<std::string, std::string> GlobalMsg
{
	{"strGetBook1","��ϲ�������ˣ��������(Ӣ�İ�)��\n������������������è����ĳ�ݶ�+0.6��ͬ���-0.3��" },
	{"strGetBook2","��ϲ�������ˣ�����è���ֲ�(Ӣ�İ�)��\n������������������è����ĳ�ݶ�+0.4��ͬ���-0.2��" },
	{"strGetBook3","��ϲ�������ˣ���è֮��(Ӣ�İ�)��\n������������!������è����ĳ�ݶ�+0.2��ͬ���-0.1��" },
	{"strGetBook4","��ϲ�������ˣ�����������\n���ǵúú�ѧϰ��~������è����ĳ�ݶ�+0.1��" },
	{"strNoExtractionTime","��Ǹ��������ĳ�ȡ�����Ѿ����ꡣ���������ԡ�" },
	{"strExtractNothing","��Ǹ����û�г����κ�ͼ��\n�������~��������è�����ͬ���+0.3��" },
	{"strGetBookMailTitle","���������ǽ����Ľ���" },
	{"strGetCardHumanMailTitle","���￨ģ��1.3.2��" },
	{"strGetCardCatMailTitle","����ģ��1.0.0��" },
	{"strGetBookMailContent","�������鵽����Ӵ~\n�ǵûظ�һ���ʼ�Ӵ����Ȼ�Ժ��ҷ����ʼ��ᱻ�ְ��ӽ�����Ͱ�ġ�" },
	{"strGetCardHumanMailContent","����Ϊ���￨ģ�塣��ӭ������" },
	{"strGetCardCatMailContent","����Ϊ����ģ�塣��ӭ������" },
	{"strGetCardHumanMessage","���￨ģ��1.3.2���Ѿ��������������~~\n�ǵûظ�һ���ʼ�Ӵ����Ȼ�Ժ��ҷ����ʼ��ᱻ�ְ��ӽ�����Ͱ�ġ�" },
	{"strGetCardCatMessage","����ģ��1.0.0���Ѿ��������������~~\n�ǵûظ�һ���ʼ�Ӵ����Ȼ�Ժ��ҷ����ʼ��ᱻ�ְ��ӽ�����Ͱ�ġ�" },
	{"pathCardOfHuman","F:\\���￨�հ�ģ��.xlsx"},
	{"pathCardOfCat","F:\\����coc7ģ��.xlsx"},
	{"pathBook1","F:\\Call of Catthulhu, Book III - Worlds of Catthulhu.pdf"},
	{"pathBook2","F:\\Call of Catthulhu, Book II - UNAUSSPRECHLICHEN KATZEN (The Cat Herders Guide).pdf"},
	{"pathBook3","F:\\Call of Catthulhu, Book I - THE NEKONOMIKON (The Book of Cats).pdf"},
	{"pathBook4","F:\\����³��������.doc"},
	{"strLogNotSupportPrivateChat","��־��¼ָ�����Ⱥ�������ã�˽������Ч" },

	{"strNameNumTooBig", "������������!������1-10֮�������!"},
	{"strNameNumCannotBeZero", "������������Ϊ��!������1-10֮�������!"},
	{"strSetInvalid", "��Ч��Ĭ����!������1-99999֮�������!"},
	{"strSetTooBig", "Ĭ��������!������1-99999֮�������!"},
	{"strSetCannotBeZero", "Ĭ��������Ϊ��!������1-99999֮�������!"},
	{"strCharacterCannotBeZero", "�������ɴ�������Ϊ��!������1-10֮�������!"},
	{"strSetInvalid", "��Ч��Ĭ����!������1-99999֮�������!"},
	{"strSetTooBig", "Ĭ��������!������1-99999֮�������!"},
	{"strSetCannotBeZero", "Ĭ��������Ϊ��!������1-99999֮�������!"},
	{"strCharacterCannotBeZero", "�������ɴ�������Ϊ��!������1-10֮�������!"},
	{"strCharacterTooBig", "�������ɴ�������!������1-10֮�������!"},
	{"strCharacterInvalid", "�������ɴ�����Ч!������1-10֮�������!"},
	{"strSCInvalid", "SC���ʽ���벻��ȷ,��ʽΪ�ɹ���San/ʧ�ܿ�San,��1/1d6!"},
	{"strSanInvalid", "Sanֵ���벻��ȷ,������1-99��Χ�ڵ�����!"},
	{"strEnValInvalid", "����ֵ���������벻��ȷ,������1-99��Χ�ڵ�����!"},
	{"strGroupIDInvalid", "��Ч��Ⱥ��!"},
	{"strSendErr", "��Ϣ����ʧ��!"},
	{"strDisabledErr", "�����޷�ִ��:���������ڴ�Ⱥ�б��ر�!"},
	{"strMEDisabledErr", "����Ա���ڴ�Ⱥ�н���.me����!"},
	{"strHELPDisabledErr", "����Ա���ڴ�Ⱥ�н���.help����!"},
	{"strNameDelErr", "û����������,�޷�ɾ��!"},
	{"strValueErr", "�������ʽ�������!"},
	{"strInputErr", "������������ʽ�������!"},
	{"strUnknownErr", "������δ֪����!"},
	{"strUnableToGetErrorMsg", "�޷���ȡ������Ϣ!"},
	{"strDiceTooBigErr", "���ﱻ���ӳ���������û��"},
	{"strRequestRetCodeErr", "���ʷ�����ʱ���ִ���! HTTP״̬��: {0}"},
	{"strRequestNoResponse", "������δ�����κ���Ϣ"},
	{"strTypeTooBigErr", "��!�������������ж�������~1...2..."},
	{"strZeroTypeErr", "����...!!ʱ����(���ﱻ���Ӳ�����ʱ���ѷ������)"},
	{"strAddDiceValErr", "������Ҫ�����������ӵ�ʲôʱ����~(��������ȷ�ļ�������:5-10֮�ڵ�����)"},
	{"strZeroDiceErr", "��?�ҵ�������?"},
	{"strRollTimeExceeded", "�������������������������!"},
	{"strRollTimeErr", "�쳣����������"},
	{"strWelcomeMsgClearNotice", "�������Ⱥ����Ⱥ��ӭ��"},
	{"strWelcomeMsgClearErr", "����:û��������Ⱥ��ӭ�ʣ����ʧ��"},
	{"strWelcomeMsgUpdateNotice", "�Ѹ��±�Ⱥ����Ⱥ��ӭ��"},
	{"strPermissionDeniedErr", "����:�˲�����ҪȺ�������ԱȨ��"},
	{"strNameTooLongErr", "����:���ƹ���(���Ϊ50Ӣ���ַ�)"},
	{"strUnknownPropErr", "����:���Բ�����"},
	{"strEmptyWWDiceErr", "��ʽ����:��ȷ��ʽΪ.w(w)XaY!����X��1, 5��Y��10"},
	{"strPropErr", "������������������Ŷ~"},
	{"strSetPropSuccess", "�������óɹ�"},
	{"strPropCleared", "�������������"},
	{"strRuleErr", "�������ݻ�ȡʧ��,������Ϣ:\n"},
	{"strRulesFailedErr", "����ʧ��,�޷��������ݿ�"},
	{"strPropDeleted", "����ɾ���ɹ�"},
	{"strPropNotFound", "����:���Բ�����"},
	{"strRuleNotFound", "δ�ҵ���Ӧ�Ĺ�����Ϣ"},
	{"strProp", "{0}��{1}����ֵΪ{2}"},
	{"strStErr", "��ʽ����:��ο������ĵ���ȡ.st�����ʹ�÷���"},
	{"strRulesFormatErr", "��ʽ����:��ȷ��ʽΪ.rules[��������:]������Ŀ ��.rules COC7:����"},
	{"strJrrp", "{0}�������Ʒֵ��: {1}"},
	{"strJrrpErr", "JRRP��ȡʧ��! ������Ϣ: \n{0}"},
	{"strGetBookCatInfo", "������³ͼ���ȡ - ���и��ʡ�\n����������         -30%\n��è֮��(Ӣ�İ�)��      - 10 % \n����è���ֲ�(Ӣ�İ�)�� - 2 % \n�������(Ӣ�İ�)��   - 0.4%\n��Ѫ�⽫��log��by���� - 0.2%\n��è֮��(���İ�)��   - 0.05% \n����è���ֲ�(���İ�)�� - 0.01 % \n�������(���İ�)��    - 0.003 % \n"},
	{"strHlpMsg" , Dice_Short_Ver + "\n" +
	R"((��������Ϊ���԰汾��Ŀ¼Ϊ������չָ�����³��������չָ�log��¼���������԰�˵����������չָ���󡿡���ͨ��ָ�)
����չָ�����³��
.cat [����]              ����³è������
.getcard human     ��ȡ���￨ģ��
.getcard cat           ��ȡ����ģ��
.getbook cat          ��ȡ����³��Ϸ������
����չָ�log��¼��
.log on Name       ��ʼ��¼��ΪName��log
.log off                ֹͣ��¼log
.log get Name      ��ȡ������Name��ʼ��log��¼
.begin Name         .log on Name ָ��ļ�
.end                      .log off ָ��ļ�
.get Name             .log get Name ָ��ļ�
�����԰�˵����
�������bug�������������ȣ���ӭ˽�ĸ��߱����ӡ�
��������빲��������˵��ļ�������ֱ��˽�ķ��������ӡ����ͨ���󽫼��뵽��getbook��ָ���С�
����չָ����
.cat                �������һֻè������
.cat 5             ���������ֻè������
.begin ģ�飺����³-����    ��ʼ��¼��Ϊ��ģ�飺����³-���ߡ���log
.begin ģ�飺����³-֧��    ��ʼ��¼��Ϊ��ģ�飺����³-֧�ߡ���log
.get ģ�飺����³-����        ��ȡ����Ϊ��ģ�飺����³-���ߡ���log��¼
.get ģ�飺����³                ͬʱ��ȡ����ģ�飺����³-���ߡ��͡�ģ�飺����³-֧�ߡ���log��¼
��ͨ�����
��ʹ��!dismiss [������QQ��]�����û������Զ���Ⱥ�������飡
���ż�¼��ɫ��: https://logpainter.kokona.tech
.r [�������ʽ*] [ԭ��]			��ͨ����
.rs	[�������ʽ*] [ԭ��]			�����
.w/ww XaY						����
.set [1-99999֮�������]			����Ĭ����
.sc SC���ʽ** [Sanֵ]			�Զ�Sancheck
.en [������] [����ֵ]			��ǿ�춨/Ļ��ɳ�
.coc7/6 [����]					COC7/6��������
.dnd [����]					DND��������
.coc7/6d					��ϸ��COC7/6��������
.ti/li					�����-��ʱ/�ܽ�֢״
.st [del/clr/show] [������] [����ֵ]		���￨����
.rc/ra [������] [����ֵ]		���ܼ춨(������/����)
.jrrp [on/off]				������Ʒ�춨
.name [cn/jp/en] [����]			�����������
.rules [��������:]������Ŀ		�����ѯ
.help						��ʾ����
<����Ⱥ/��������>
.ri [��ֵ] [�ǳ�]			DnD�ȹ�����
.init [clr]					DnD�ȹ��鿴/���
.nn [����]					����/ɾ���ǳ�
.nnn [cn/jp/en]				��������ǳ�
.rh [�������ʽ*] [ԭ��]			����,���˽�ķ���
.bot [on/off] [������QQ��]		�����˿�����ر�
.ob [exit/list/clr/on/off]			�Թ�ģʽ
.me on/off/����				�Ե������ӽ���������
.welcome ��ӭ��Ϣ				Ⱥ��ӭ��ʾ
<����˽��>
.me Ⱥ�� ����				�Ե������ӽ���������
*COC7�ͷ���ΪP+����,������ΪB+����
 ֧��ʹ��K��ȡ�ϴ�ļ�������
 ֧��ʹ�� ����#���ʽ ���ж�������
**SC���ʽΪ �ɹ���San/ʧ�ܿ�San,��:1/1d6
�������/bug����/�鿴Դ�������QQȺ941980833��624807593(����))"}
};