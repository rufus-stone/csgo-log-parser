#pragma once

#include <string_view>

namespace csgoprs::log_samples
{

using namespace std::string_view_literals;

constexpr auto competitive_cs_agency = R"###(
L 05/04/2020 - 21:49:30: World triggered "Match_Start" on "cs_agency"
L 05/04/2020 - 21:49:33: "Alice<8><STEAM_1:1:00000001><CT>" purchased "item_kevlar"
L 05/04/2020 - 21:49:33: "Bob<6><STEAM_1:0:00000002><CT>" purchased "deagle"
L 05/04/2020 - 21:49:33: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:49:34: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "deagle"
L 05/04/2020 - 21:49:34: "Alice<8><STEAM_1:1:00000001><CT>" purchased "decoy"
L 05/04/2020 - 21:49:34: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "tec9"
L 05/04/2020 - 21:49:45: World triggered "Round_Start"
L 05/04/2020 - 21:49:46: "Bob<6><STEAM_1:0:00000002><CT>" left buyzone with [ weapon_knife weapon_deagle ]
L 05/04/2020 - 21:49:46: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_decoy kevlar(100) ]
L 05/04/2020 - 21:49:47: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock kevlar(100) ]
L 05/04/2020 - 21:49:47: "Mark<7><STEAM_1:1:00000006><CT>" left buyzone with [ weapon_knife weapon_hkp2000 ]
L 05/04/2020 - 21:49:47: "Dean<9><STEAM_1:1:00000004><TERRORIST>" left buyzone with [ weapon_knife_t weapon_deagle ]
L 05/04/2020 - 21:49:51: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_tec9 ]
L 05/04/2020 - 21:49:52: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock kevlar(100) ]
L 05/04/2020 - 21:49:54: "Mark<7><STEAM_1:1:00000006><CT>" [-258 -1069 380] killed other "func_breakable<479>" [-257 -1024 444] with "hkp2000"
L 05/04/2020 - 21:49:56: "Alice<8><STEAM_1:1:00000001><CT>" [109 -1254 669] killed other "func_breakable<480>" [-325 -1092 444] with "usp_silencer"
L 05/04/2020 - 21:49:56: "Alice<8><STEAM_1:1:00000001><CT>" [88 -1242 664] killed other "func_breakable<478>" [-189 -956 444] with "usp_silencer"
L 05/04/2020 - 21:49:57: "Alice<8><STEAM_1:1:00000001><CT>" [69 -1232 659] killed other "func_breakable<477>" [-121 -888 444] with "usp_silencer"
L 05/04/2020 - 21:49:57: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-62 1068 512] killed other "func_breakable<446>" [-50 990 534] with "glock"
L 05/04/2020 - 21:50:03: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1156 -582 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1119 -1044 430] with "deagle" (damage "51") (damage_armor "0") (health "49") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:50:03: "Bob<6><STEAM_1:0:00000002><CT>" [-1123 -1020 442] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1158 -565 512] with "deagle" (damage "51") (damage_armor "0") (health "49") (armor "0") (hitgroup "right arm")
L 05/04/2020 - 21:50:03: "Bob<6><STEAM_1:0:00000002><CT>" [-1123 -1020 442] killed other "func_breakable<459>" [-1206 -348 568] with "deagle" (penetrated)
L 05/04/2020 - 21:50:03: "Mark<7><STEAM_1:1:00000006><CT>" [-621 -1037 320] killed other "func_breakable<437>" [-1071 -656 534] with "hkp2000"
L 05/04/2020 - 21:50:03: "Bob<6><STEAM_1:0:00000002><CT>" [-1123 -1020 442] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1158 -565 512] with "deagle" (damage "52") (damage_armor "0") (health "0") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:50:03: "Bob<6><STEAM_1:0:00000002><CT>" [-1123 -1020 442] killed "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1158 -565 576] with "deagle"
L 05/04/2020 - 21:50:10: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-691 -146 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-978 -73 512] with "glock" (damage "27") (damage_armor "0") (health "22") (armor "0") (hitgroup "right arm")
L 05/04/2020 - 21:50:10: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-704 -146 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1003 -105 512] with "glock" (damage "27") (damage_armor "0") (health "0") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:50:10: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-704 -146 512] killed "Bob<6><STEAM_1:0:00000002><CT>" [-1003 -105 576] with "glock"
L 05/04/2020 - 21:50:10: "Dean<9><STEAM_1:1:00000004><TERRORIST>" assisted killing "Bob<6><STEAM_1:0:00000002><CT>"
L 05/04/2020 - 21:50:11: "Mark<7><STEAM_1:1:00000006><CT>" [-1100 -272 512] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-737 -141 512] with "hkp2000" (damage "16") (damage_armor "8") (health "84") (armor "91") (hitgroup "left arm")
L 05/04/2020 - 21:50:11: "Mark<7><STEAM_1:1:00000006><CT>" [-1099 -270 512] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-765 -138 512] with "hkp2000" (damage "20") (damage_armor "10") (health "64") (armor "80") (hitgroup "stomach")
L 05/04/2020 - 21:50:11: "Mark<7><STEAM_1:1:00000006><CT>" [-1099 -270 512] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-794 -137 512] with "hkp2000" (damage "131") (damage_armor "0") (health "0") (armor "80") (hitgroup "head")
L 05/04/2020 - 21:50:11: "Mark<7><STEAM_1:1:00000006><CT>" [-1099 -270 512] killed "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-794 -137 576] with "hkp2000" (headshot)
L 05/04/2020 - 21:50:12: "Mark<7><STEAM_1:1:00000006><CT>" [-1099 -270 512] killed other "func_breakable<458>" [-676 -58 568] with "hkp2000"
L 05/04/2020 - 21:50:23: "Alice<8><STEAM_1:1:00000001><CT>" [-279 1178 512] killed other "func_breakable<514>" [-591 1444 588] with "usp_silencer"
L 05/04/2020 - 21:50:24: "Alice<8><STEAM_1:1:00000001><CT>" [-337 1234 512] killed other "func_breakable<517>" [-471 1444 588] with "usp_silencer"
L 05/04/2020 - 21:50:24: "Alice<8><STEAM_1:1:00000001><CT>" [-358 1286 512] killed other "func_breakable<518>" [-350 1444 588] with "usp_silencer"
L 05/04/2020 - 21:50:24: "Alice<8><STEAM_1:1:00000001><CT>" [-358 1286 512] killed other "func_breakable<523>" [-350 1724 588] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:50:27: "Alice<8><STEAM_1:1:00000001><CT>" [-385 1576 512] killed other "func_breakable<522>" [-471 1724 588] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:50:28: "Alice<8><STEAM_1:1:00000001><CT>" [-405 1593 512] killed other "func_breakable<519>" [-591 1724 588] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:50:30: "Alice<8><STEAM_1:1:00000001><CT>" threw decoy [-239 -2594 -8318]
L 05/04/2020 - 21:50:32: "Alice<8><STEAM_1:1:00000001><CT>" [-767 1818 512] killed other "func_breakable<490>" [-912 1981 566] with "usp_silencer"
L 05/04/2020 - 21:50:32: "Alice<8><STEAM_1:1:00000001><CT>" [-777 1887 512] killed other "func_breakable<489>" [-1008 1981 566] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:50:33: "Alice<8><STEAM_1:1:00000001><CT>" [-1066 1926 512] killed other "func_breakable<320>" [-1576 1652 566] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:50:35: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer kevlar(100) ]
L 05/04/2020 - 21:50:36: "James<3><STEAM_1:0:00000005><TERRORIST>" [-446 1203 512] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-907 1098 512] with "tec9" (damage "33") (damage_armor "0") (health "67") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:50:36: "James<3><STEAM_1:0:00000005><TERRORIST>" [-481 1185 512] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-907 1098 512] with "tec9" (damage "33") (damage_armor "0") (health "34") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:50:36: "James<3><STEAM_1:0:00000005><TERRORIST>" [-509 1175 512] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-907 1098 512] with "tec9" (damage "20") (damage_armor "0") (health "14") (armor "0") (hitgroup "left leg")
L 05/04/2020 - 21:50:36: "James<3><STEAM_1:0:00000005><TERRORIST>" [-562 1162 512] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-907 1098 512] with "tec9" (damage "35") (damage_armor "0") (health "0") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:50:36: "James<3><STEAM_1:0:00000005><TERRORIST>" [-562 1162 512] killed "Mark<7><STEAM_1:1:00000006><CT>" [-907 1098 576] with "tec9"
L 05/04/2020 - 21:50:42: "Alice<8><STEAM_1:1:00000001><CT>" triggered "Touched_A_Hostage"
L 05/04/2020 - 21:50:42: "Alice<8><STEAM_1:1:00000001><CT>" [-1276 1155 512] picked up a hostage
L 05/04/2020 - 21:50:51: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer kevlar(100) ]
L 05/04/2020 - 21:51:08: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_tec9 ]
L 05/04/2020 - 21:51:20: "James<3><STEAM_1:0:00000005><TERRORIST>" [-234 -1463 256] killed other "func_breakable<481>" [-393 -1160 444] with "tec9"
L 05/04/2020 - 21:51:32: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_tec9 ]
L 05/04/2020 - 21:51:47: "James<3><STEAM_1:0:00000005><TERRORIST>" [-382 -1187 256] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-156 -1131 320] with "tec9" (damage "26") (damage_armor "1") (health "41") (armor "98") (hitgroup "chest")
L 05/04/2020 - 21:51:47: "James<3><STEAM_1:0:00000005><TERRORIST>" [-363 -1201 256] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-133 -1154 303] with "tec9" (damage "26") (damage_armor "1") (health "15") (armor "96") (hitgroup "right arm")
L 05/04/2020 - 21:51:48: "James<3><STEAM_1:0:00000005><TERRORIST>" [-248 -1240 256] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-101 -1183 284] with "tec9" (damage "34") (damage_armor "1") (health "0") (armor "94") (hitgroup "stomach")
L 05/04/2020 - 21:51:48: "Alice<8><STEAM_1:1:00000001><CT>" [-101 -1183 284] dropped off a hostage
L 05/04/2020 - 21:51:48: "James<3><STEAM_1:0:00000005><TERRORIST>" [-248 -1240 256] killed "Alice<8><STEAM_1:1:00000001><CT>" [-101 -1183 348] with "tec9"
L 05/04/2020 - 21:51:48: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "0") (T "1")
L 05/04/2020 - 21:51:48: Team "CT" scored "0" with "3" players
L 05/04/2020 - 21:51:48: Team "TERRORIST" scored "1" with "3" players
L 05/04/2020 - 21:51:48: World triggered "Round_End"
L 05/04/2020 - 21:51:55: Starting Freeze period
L 05/04/2020 - 21:51:58: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:51:58: "Alice<8><STEAM_1:1:00000001><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:51:58: "Bob<6><STEAM_1:0:00000002><CT>" purchased "m4a1_silencer"
L 05/04/2020 - 21:51:59: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:52:00: "Alice<8><STEAM_1:1:00000001><CT>" purchased "hegrenade"
L 05/04/2020 - 21:52:00: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:52:01: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "galilar"
L 05/04/2020 - 21:52:01: "Mark<7><STEAM_1:1:00000006><CT>" purchased "mag7"
L 05/04/2020 - 21:52:02: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:52:02: "Alice<8><STEAM_1:1:00000001><CT>" purchased "elite"
L 05/04/2020 - 21:52:03: "Mark<7><STEAM_1:1:00000006><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:52:04: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 21:52:04: "Alice<8><STEAM_1:1:00000001><CT>" purchased "ump45"
L 05/04/2020 - 21:52:04: "Mark<7><STEAM_1:1:00000006><CT>" purchased "item_defuser"
L 05/04/2020 - 21:52:07: "Mark<7><STEAM_1:1:00000006><CT>" purchased "incgrenade"
L 05/04/2020 - 21:52:07: "Mark<7><STEAM_1:1:00000006><CT>" purchased "flashbang"
L 05/04/2020 - 21:52:10: World triggered "Round_Start"
L 05/04/2020 - 21:52:11: "Dean<9><STEAM_1:1:00000004><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 ]
L 05/04/2020 - 21:52:11: "Bob<6><STEAM_1:0:00000002><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_m4a1_silencer ]
L 05/04/2020 - 21:52:11: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_elite weapon_hegrenade weapon_ump45 kevlar(100) helmet ]
L 05/04/2020 - 21:52:11: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_tec9 weapon_sg556 weapon_flashbang kevlar(100) ]
L 05/04/2020 - 21:52:12: "Mark<7><STEAM_1:1:00000006><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_mag7 weapon_incgrenade weapon_flashbang defuser kevlar(100) helmet ]
L 05/04/2020 - 21:52:13: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_galilar kevlar(100) helmet ]
L 05/04/2020 - 21:52:19: "Bob<6><STEAM_1:0:00000002><CT>" [-1309 -518 320] killed other "func_breakable<404>" [-1345 510 540] with "m4a1_silencer"
L 05/04/2020 - 21:52:19: "Bob<6><STEAM_1:0:00000002><CT>" [-1309 -518 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1318 552 512] with "m4a1" (damage "18") (damage_armor "3") (health "82") (armor "96") (hitgroup "stomach")
L 05/04/2020 - 21:52:20: "Bob<6><STEAM_1:0:00000002><CT>" [-1291 -508 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] with "m4a1" (damage "22") (damage_armor "4") (health "60") (armor "91") (hitgroup "chest")
L 05/04/2020 - 21:52:20: "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] with "m4a1" (damage "22") (damage_armor "4") (health "38") (armor "86") (hitgroup "chest")
L 05/04/2020 - 21:52:21: "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] with "m4a1" (damage "22") (damage_armor "4") (health "16") (armor "81") (hitgroup "chest")
L 05/04/2020 - 21:52:21: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] with "sg556" (damage "28") (damage_armor "0") (health "72") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:52:21: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] with "sg556" (damage "35") (damage_armor "0") (health "37") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:52:21: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] with "sg556" (damage "28") (damage_armor "0") (health "9") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:52:21: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 320] with "sg556" (damage "28") (damage_armor "0") (health "0") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:52:21: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1332 538 512] killed "Bob<6><STEAM_1:0:00000002><CT>" [-1290 -508 384] with "sg556"
L 05/04/2020 - 21:52:22: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1300 549 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-1385 -634 320] with "galilar" (damage "27") (damage_armor "4") (health "73") (armor "95") (hitgroup "stomach")
L 05/04/2020 - 21:52:22: "Alice<8><STEAM_1:1:00000001><CT>" [-1385 -634 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1300 549 512] with "ump45" (damage "46") (damage_armor "12") (health "54") (armor "87") (hitgroup "head")
L 05/04/2020 - 21:52:22: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1300 549 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-1385 -634 320] with "galilar" (damage "88") (damage_armor "12") (health "0") (armor "82") (hitgroup "head")
L 05/04/2020 - 21:52:22: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1300 549 512] killed "Alice<8><STEAM_1:1:00000001><CT>" [-1385 -634 384] with "galilar" (headshot)
L 05/04/2020 - 21:52:39: "Mark<7><STEAM_1:1:00000006><CT>" [-268 -466 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-426 -919 320] with "mag7" (damage "10") (damage_armor "1") (health "6") (armor "79") (hitgroup "right arm")
L 05/04/2020 - 21:52:39: "James<3><STEAM_1:0:00000005><TERRORIST>" [-426 -919 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-267 -467 320] with "sg556" (damage "36") (damage_armor "0") (health "64") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:52:39: "James<3><STEAM_1:0:00000005><TERRORIST>" [-426 -919 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-268 -466 320] with "sg556" (damage "36") (damage_armor "0") (health "28") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:52:39: "James<3><STEAM_1:0:00000005><TERRORIST>" [-426 -919 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-268 -466 320] with "sg556" (damage "29") (damage_armor "0") (health "0") (armor "100") (hitgroup "chest")
L 05/04/2020 - 21:52:39: "James<3><STEAM_1:0:00000005><TERRORIST>" [-426 -919 320] killed "Mark<7><STEAM_1:1:00000006><CT>" [-268 -466 384] with "sg556"
L 05/04/2020 - 21:52:39: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "0") (T "2")
L 05/04/2020 - 21:52:39: Team "CT" scored "0" with "3" players
L 05/04/2020 - 21:52:39: Team "TERRORIST" scored "2" with "3" players
L 05/04/2020 - 21:52:39: World triggered "Round_End"
L 05/04/2020 - 21:52:43: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-633 -1025 320] killed other "func_breakable<480>" [-325 -1092 444] with "galilar"
L 05/04/2020 - 21:52:43: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-576 -1037 320] killed other "func_breakable<479>" [-257 -1024 444] with "galilar"
L 05/04/2020 - 21:52:43: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-413 -726 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-58 -1253 256] with "sg556" (damage "9") (damage_armor "0") (health "0") (armor "79") (hitgroup "chest")
L 05/04/2020 - 21:52:43: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-413 -726 320] killed "James<3><STEAM_1:0:00000005><TERRORIST>" [-58 -1253 320] with "sg556"
L 05/04/2020 - 21:52:43: "Bob<6><STEAM_1:0:00000002><CT>" assisted killing "James<3><STEAM_1:0:00000005><TERRORIST>"
L 05/04/2020 - 21:52:43: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-476 -1032 320] killed other "func_breakable<474>" [-121 -888 592] with "galilar"
L 05/04/2020 - 21:52:44: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-406 -1008 320] killed other "func_breakable<476>" [-76 -844 444] with "galilar" (penetrated)
L 05/04/2020 - 21:52:45: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-271 -950 320] killed other "func_breakable<477>" [-121 -888 444] with "galilar" (penetrated)
L 05/04/2020 - 21:52:46: Starting Freeze period
L 05/04/2020 - 21:52:49: "Alice<8><STEAM_1:1:00000001><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:52:49: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:52:50: "Bob<6><STEAM_1:0:00000002><CT>" purchased "ssg08"
L 05/04/2020 - 21:52:50: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:52:50: "Alice<8><STEAM_1:1:00000001><CT>" purchased "hegrenade"
L 05/04/2020 - 21:52:51: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:52:51: "Mark<7><STEAM_1:1:00000006><CT>" purchased "p90"
L 05/04/2020 - 21:52:52: "Bob<6><STEAM_1:0:00000002><CT>" purchased "item_kevlar"
L 05/04/2020 - 21:52:52: "Alice<8><STEAM_1:1:00000001><CT>" purchased "nova"
L 05/04/2020 - 21:52:53: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:52:53: "Alice<8><STEAM_1:1:00000001><CT>" purchased "decoy"
L 05/04/2020 - 21:53:02: World triggered "Round_Start"
L 05/04/2020 - 21:53:02: "Alice<8><STEAM_1:1:00000001><CT>" [501 -1556 410] killed other "func_breakable<781>" [-121 -888 592] with "usp_silencer"
L 05/04/2020 - 21:53:03: "Dean<9><STEAM_1:1:00000004><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_hegrenade ]
L 05/04/2020 - 21:53:03: "Alice<8><STEAM_1:1:00000001><CT>" [404 -1458 410] killed other "func_breakable<473>" [-189 -956 592] with "usp_silencer"
L 05/04/2020 - 21:53:03: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_hegrenade weapon_nova weapon_decoy kevlar(100) helmet ]
L 05/04/2020 - 21:53:03: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 kevlar(100) ]
L 05/04/2020 - 21:53:03: "Alice<8><STEAM_1:1:00000001><CT>" [325 -1391 400] killed other "func_breakable<478>" [-189 -956 444] with "usp_silencer"
L 05/04/2020 - 21:53:03: "Bob<6><STEAM_1:0:00000002><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_ssg08 kevlar(100) ]
L 05/04/2020 - 21:53:03: "Mark<7><STEAM_1:1:00000006><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_p90 ]
L 05/04/2020 - 21:53:04: "Alice<8><STEAM_1:1:00000001><CT>" [262 -1338 313] killed other "func_breakable<783>" [-121 -888 444] with "usp_silencer"
L 05/04/2020 - 21:53:04: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 kevlar(100) helmet ]
L 05/04/2020 - 21:53:07: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1556 1349 512] killed other "func_breakable<542>" [-1494 1028 568] with "sg556"
L 05/04/2020 - 21:53:12: "Dean<9><STEAM_1:1:00000004><TERRORIST>" threw hegrenade [-1315 -482 350]
L 05/04/2020 - 21:53:12: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1476 559 512] killed other "func_breakable<182>" [-1264 -588 372] with "hegrenade"
L 05/04/2020 - 21:53:12: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1476 559 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1261 -800 320] with "hegrenade" (damage "1") (damage_armor "0") (health "99") (armor "99") (hitgroup "generic")
L 05/04/2020 - 21:53:12: "Bob<6><STEAM_1:0:00000002><CT>" [-1263 -800 320] killed other "func_breakable<401>" [-1472 510 540] with "ssg08"
L 05/04/2020 - 21:53:12: "Bob<6><STEAM_1:0:00000002><CT>" [-1263 -800 320] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1487 561 512] with "ssg08" (damage "77") (damage_armor "0") (health "23") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:53:12: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-1490 561 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1243 -797 320] with "sg556" (damage "35") (damage_armor "0") (health "64") (armor "99") (hitgroup "stomach")
L 05/04/2020 - 21:53:21: "Bob<6><STEAM_1:0:00000002><CT>" [-1452 -747 320] killed other "func_breakable<403>" [-1409 510 540] with "ssg08"
L 05/04/2020 - 21:53:27: "Mark<7><STEAM_1:1:00000006><CT>" [48 277 512] killed other "func_breakable<447>" [14 990 534] with "p90"
L 05/04/2020 - 21:53:27: "Mark<7><STEAM_1:1:00000006><CT>" [48 277 512] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [27 1012 512] with "p90" (damage "15") (damage_armor "0") (health "8") (armor "0") (hitgroup "left leg")
L 05/04/2020 - 21:53:27: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [27 1012 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-25 812 320] with "sg556" (damage "22") (damage_armor "0") (health "73") (armor "100") (hitgroup "right leg")
L 05/04/2020 - 21:53:27: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [27 1012 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-49 826 320] with "sg556" (damage "118") (damage_armor "0") (health "0") (armor "100") (hitgroup "head")
L 05/04/2020 - 21:53:27: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [27 1012 512] killed "Alice<8><STEAM_1:1:00000001><CT>" [-49 826 384] with "sg556" (headshot)
L 05/04/2020 - 21:53:29: "Mark<7><STEAM_1:1:00000006><CT>" [66 190 512] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-72 1094 512] with "p90" (damage "24") (damage_armor "0") (health "0") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:53:29: "Mark<7><STEAM_1:1:00000006><CT>" [66 190 512] killed "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-72 1094 576] with "p90"
L 05/04/2020 - 21:53:29: "Bob<6><STEAM_1:0:00000002><CT>" assisted killing "Dean<9><STEAM_1:1:00000004><TERRORIST>"
L 05/04/2020 - 21:53:31: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1437 584 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1276 -793 320] with "sg556" (damage "35") (damage_armor "0") (health "29") (armor "99") (hitgroup "stomach")
L 05/04/2020 - 21:53:31: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1395 584 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1269 -792 320] with "sg556" (damage "21") (damage_armor "0") (health "8") (armor "99") (hitgroup "left leg")
L 05/04/2020 - 21:53:33: "Bob<6><STEAM_1:0:00000002><CT>" [-1357 -795 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1427 580 512] with "ssg08" (damage "70") (damage_armor "6") (health "30") (armor "93") (hitgroup "right arm")
L 05/04/2020 - 21:53:37: "Bob<6><STEAM_1:0:00000002><CT>" [-1462 -786 320] killed other "func_breakable<404>" [-1345 510 540] with "ssg08"
L 05/04/2020 - 21:53:37: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1383 580 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1462 -786 320] with "sg556" (damage "28") (damage_armor "0") (health "0") (armor "99") (hitgroup "chest")
L 05/04/2020 - 21:53:37: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1383 580 512] killed "Bob<6><STEAM_1:0:00000002><CT>" [-1462 -786 384] with "sg556"
L 05/04/2020 - 21:54:07: "Mark<7><STEAM_1:1:00000006><CT>" triggered "Touched_A_Hostage"
L 05/04/2020 - 21:54:07: "Mark<7><STEAM_1:1:00000006><CT>" [-1294 1121 512] picked up a hostage
L 05/04/2020 - 21:54:29: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1124 -793 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] with "sg556" (damage "1") (damage_armor "0") (health "94") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:54:29: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1132 -790 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] with "sg556" (damage "29") (damage_armor "0") (health "65") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:54:30: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1135 -789 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] with "sg556" (damage "29") (damage_armor "0") (health "36") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:54:30: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1135 -789 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] with "sg556" (damage "29") (damage_armor "0") (health "7") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:54:30: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1135 -789 320] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] with "sg556" (damage "29") (damage_armor "0") (health "0") (armor "0") (hitgroup "right arm")
L 05/04/2020 - 21:54:30: "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 320] dropped off a hostage
L 05/04/2020 - 21:54:30: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1135 -789 320] killed "Mark<7><STEAM_1:1:00000006><CT>" [-1598 -600 366] with "sg556"
L 05/04/2020 - 21:54:30: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "0") (T "3")
L 05/04/2020 - 21:54:30: Team "CT" scored "0" with "3" players
L 05/04/2020 - 21:54:30: Team "TERRORIST" scored "3" with "3" players
L 05/04/2020 - 21:54:30: World triggered "Round_End"
L 05/04/2020 - 21:54:34: "James<3><STEAM_1:0:00000005><TERRORIST>" [-606 -1039 320] killed other "func_breakable<470>" [-393 -1160 592] with "sg556"
L 05/04/2020 - 21:54:35: "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-40 -1224 256] killed other "func_breakable<481>" [-393 -1160 444] with "sg556"
L 05/04/2020 - 21:54:35: "James<3><STEAM_1:0:00000005><TERRORIST>" [-495 -1000 320] killed other "func_breakable<472>" [-257 -1024 592] with "sg556"
L 05/04/2020 - 21:54:37: Starting Freeze period
L 05/04/2020 - 21:54:39: "Bob<6><STEAM_1:0:00000002><CT>" purchased "aug"
L 05/04/2020 - 21:54:41: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:54:41: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:54:41: "Mark<7><STEAM_1:1:00000006><CT>" purchased "aug"
L 05/04/2020 - 21:54:41: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:54:42: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:54:42: "Bob<6><STEAM_1:0:00000002><CT>" purchased "flashbang"
L 05/04/2020 - 21:54:43: "Mark<7><STEAM_1:1:00000006><CT>" purchased "item_kevlar"
L 05/04/2020 - 21:54:43: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 21:54:44: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 21:54:45: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "smokegrenade"
L 05/04/2020 - 21:54:46: "Mark<7><STEAM_1:1:00000006><CT>" purchased "hegrenade"
L 05/04/2020 - 21:54:47: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "molotov"
L 05/04/2020 - 21:54:52: World triggered "Round_Start"
L 05/04/2020 - 21:54:53: "Alice<8><STEAM_1:1:00000001><CT>" purchased "aug"
L 05/04/2020 - 21:54:54: "Dean<9><STEAM_1:1:00000004><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_molotov kevlar(100) helmet ]
L 05/04/2020 - 21:54:54: "Bob<6><STEAM_1:0:00000002><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_aug weapon_flashbang ]
L 05/04/2020 - 21:54:54: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 kevlar(100) helmet ]
L 05/04/2020 - 21:54:54: "Alice<8><STEAM_1:1:00000001><CT>" purchased "taser"
L 05/04/2020 - 21:54:54: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_hegrenade weapon_flashbang weapon_smokegrenade kevlar(100) helmet ]
L 05/04/2020 - 21:54:55: "Mark<7><STEAM_1:1:00000006><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_aug weapon_hegrenade kevlar(100) ]
L 05/04/2020 - 21:54:57: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_aug weapon_taser ]
L 05/04/2020 - 21:54:59: "Alice<8><STEAM_1:1:00000001><CT>" [-41 -1188 259] killed other "func_breakable<758>" [-257 -1024 592] with "usp_silencer"
L 05/04/2020 - 21:55:01: "Bob<6><STEAM_1:0:00000002><CT>" threw flashbang [-1311 -377 329] flashbang entindex 478)
L 05/04/2020 - 21:55:01: "James<3><STEAM_1:0:00000005><TERRORIST>" blinded for 3.68 by "Bob<6><STEAM_1:0:00000002><CT>" from flashbang entindex 478 
L 05/04/2020 - 21:55:11: "Mark<7><STEAM_1:1:00000006><CT>" [-512 -17 512] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1020 532 512] with "hkp2000" (damage "15") (damage_armor "7") (health "85") (armor "92") (hitgroup "chest")
L 05/04/2020 - 21:55:12: "Mark<7><STEAM_1:1:00000006><CT>" [-512 -17 512] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-1017 532 512] with "hkp2000" (damage "61") (damage_armor "30") (health "24") (armor "61") (hitgroup "head")
L 05/04/2020 - 21:55:12: Molotov projectile spawned at -602.358887 696.281433 581.419556, velocity 199.928925 -605.474182 227.317413
L 05/04/2020 - 21:55:13: "Alice<8><STEAM_1:1:00000001><CT>" [-487 265 512] killed other "func_breakable<411>" [-896 510 540] with "aug"
L 05/04/2020 - 21:55:13: "James<3><STEAM_1:0:00000005><TERRORIST>" [-951 559 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-488 265 512] with "sg556" (damage "117") (damage_armor "0") (health "0") (armor "0") (hitgroup "head")
L 05/04/2020 - 21:55:13: "James<3><STEAM_1:0:00000005><TERRORIST>" [-951 559 512] killed "Alice<8><STEAM_1:1:00000001><CT>" [-488 265 558] with "sg556" (headshot)
L 05/04/2020 - 21:55:13: "James<3><STEAM_1:0:00000005><TERRORIST>" [-951 559 512] killed other "func_breakable<417>" [-559 322 534] with "sg556"
L 05/04/2020 - 21:55:14: "Dean<9><STEAM_1:1:00000004><TERRORIST>" threw molotov [-471 155 514]
L 05/04/2020 - 21:55:15: "James<3><STEAM_1:0:00000005><TERRORIST>" [-783 546 512] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-549 -9 512] with "sg556" (damage "117") (damage_armor "0") (health "0") (armor "100") (hitgroup "head")
L 05/04/2020 - 21:55:15: "James<3><STEAM_1:0:00000005><TERRORIST>" [-783 546 512] killed "Mark<7><STEAM_1:1:00000006><CT>" [-549 -9 576] with "sg556" (headshot)
L 05/04/2020 - 21:55:15: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-618 720 512] killed other "func_breakable<418>" [-568 258 534] with "inferno"
L 05/04/2020 - 21:55:15: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-618 720 512] killed other "func_breakable<419>" [-576 208 534] with "inferno"
L 05/04/2020 - 21:55:16: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-618 720 512] killed other "func_breakable<421>" [-609 190 534] with "inferno"
L 05/04/2020 - 21:55:16: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-618 720 512] killed other "func_breakable<423>" [-682 184 534] with "inferno"
L 05/04/2020 - 21:55:16: "Bob<6><STEAM_1:0:00000002><CT>" [-1453 -261 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1312 229 320] with "aug" (damage "24") (damage_armor "1") (health "76") (armor "98") (hitgroup "chest")
L 05/04/2020 - 21:55:17: "Bob<6><STEAM_1:0:00000002><CT>" [-1451 -261 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1350 230 320] with "aug" (damage "24") (damage_armor "1") (health "52") (armor "96") (hitgroup "chest")
L 05/04/2020 - 21:55:17: "Bob<6><STEAM_1:0:00000002><CT>" [-1451 -261 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1358 230 320] with "aug" (damage "98") (damage_armor "5") (health "0") (armor "90") (hitgroup "head")
L 05/04/2020 - 21:55:17: "Bob<6><STEAM_1:0:00000002><CT>" [-1451 -261 320] killed "Sam<5><STEAM_1:0:00000003><TERRORIST>" [-1358 230 384] with "aug" (headshot)
L 05/04/2020 - 21:55:20: "Bob<6><STEAM_1:0:00000002><CT>" [-1438 -78 320] attacked "James<3><STEAM_1:0:00000005><TERRORIST>" [-870 532 512] with "aug" (damage "30") (damage_armor "1") (health "0") (armor "59") (hitgroup "stomach")
L 05/04/2020 - 21:55:20: "Bob<6><STEAM_1:0:00000002><CT>" [-1438 -78 320] killed "James<3><STEAM_1:0:00000005><TERRORIST>" [-870 532 576] with "aug"
L 05/04/2020 - 21:55:20: "Mark<7><STEAM_1:1:00000006><CT>" assisted killing "James<3><STEAM_1:0:00000005><TERRORIST>"
L 05/04/2020 - 21:55:26: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-601 664 512] killed other "func_breakable<410>" [-752 506 540] with "sg556"
L 05/04/2020 - 21:55:26: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-601 664 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1438 -69 320] with "sg556" (damage "73") (damage_armor "0") (health "27") (armor "0") (hitgroup "head")
L 05/04/2020 - 21:55:27: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-601 664 512] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-1438 -69 320] with "sg556" (damage "114") (damage_armor "0") (health "0") (armor "0") (hitgroup "head")
L 05/04/2020 - 21:55:27: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-601 664 512] killed "Bob<6><STEAM_1:0:00000002><CT>" [-1438 -69 384] with "sg556" (headshot)
L 05/04/2020 - 21:55:27: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "0") (T "4")
L 05/04/2020 - 21:55:27: Team "CT" scored "0" with "3" players
L 05/04/2020 - 21:55:27: Team "TERRORIST" scored "4" with "3" players
L 05/04/2020 - 21:55:27: World triggered "Round_End"
L 05/04/2020 - 21:55:34: Starting Freeze period
L 05/04/2020 - 21:55:36: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:55:37: "Alice<8><STEAM_1:1:00000001><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:55:37: "Mark<7><STEAM_1:1:00000006><CT>" purchased "ssg08"
L 05/04/2020 - 21:55:37: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:55:37: "Alice<8><STEAM_1:1:00000001><CT>" purchased "item_defuser"
L 05/04/2020 - 21:55:38: "Alice<8><STEAM_1:1:00000001><CT>" purchased "taser"
L 05/04/2020 - 21:55:38: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:55:39: "Sam<5><STEAM_1:0:00000003><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:55:39: "Mark<7><STEAM_1:1:00000006><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:55:39: "Mark<7><STEAM_1:1:00000006><CT>" purchased "item_defuser"
L 05/04/2020 - 21:55:40: "Alice<8><STEAM_1:1:00000001><CT>" purchased "flashbang"
L 05/04/2020 - 21:55:40: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 21:55:41: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 21:55:41: "James<3><STEAM_1:0:00000005><TERRORIST>" purchased "hegrenade"
L 05/04/2020 - 21:55:42: "Mark<7><STEAM_1:1:00000006><CT>" purchased "hegrenade"
L 05/04/2020 - 21:55:42: "Alice<8><STEAM_1:1:00000001><CT>" purchased "decoy"
L 05/04/2020 - 21:55:42: "Alice<8><STEAM_1:1:00000001><CT>" purchased "flashbang"
L 05/04/2020 - 21:55:42: "Alice<8><STEAM_1:1:00000001><CT>" purchased "smokegrenade"
L 05/04/2020 - 21:55:44: "Dean<9><STEAM_1:1:00000004><TERRORIST>" purchased "molotov"
L 05/04/2020 - 21:55:46: "Bob<6><STEAM_1:0:00000002><CT>" purchased "aug"
L 05/04/2020 - 21:55:49: World triggered "Round_Start"
L 05/04/2020 - 21:55:49: "Bob<6><STEAM_1:0:00000002><CT>" purchased "item_kevlar"
L 05/04/2020 - 21:55:50: "James<3><STEAM_1:0:00000005><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_flashbang weapon_hegrenade kevlar(100) helmet ]
L 05/04/2020 - 21:55:50: "Alice<8><STEAM_1:1:00000001><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_taser weapon_flashbang weapon_decoy weapon_smokegrenade defuser kevlar(100) helmet ]
L 05/04/2020 - 21:55:50: "Sam<5><STEAM_1:0:00000003><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 kevlar(100) helmet ]
L 05/04/2020 - 21:55:51: "Mark<7><STEAM_1:1:00000006><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_ssg08 weapon_hegrenade defuser kevlar(100) helmet ]
L 05/04/2020 - 21:55:52: "Dean<9><STEAM_1:1:00000004><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_taser weapon_molotov kevlar(100) helmet ]
L 05/04/2020 - 21:55:53: "Bob<6><STEAM_1:0:00000002><CT>" left buyzone with [ weapon_knife weapon_usp_silencer weapon_aug kevlar(100) ]
L 05/04/2020 - 21:55:55: "Bob<6><STEAM_1:0:00000002><CT>" [889 -873 256] killed other "func_breakable<556>" [764 -320 326] with "usp_silencer" (penetrated)
L 05/04/2020 - 21:55:57: "James<3><STEAM_1:0:00000005><TERRORIST>" threw flashbang [-1247 -349 384] flashbang entindex 572)
L 05/04/2020 - 21:56:00: "Alice<8><STEAM_1:1:00000001><CT>" [-1120 -565 512] killed other "func_breakable<463>" [-1066 -348 568] with "usp_silencer"
L 05/04/2020 - 21:56:00: Molotov projectile spawned at -617.943237 507.695740 580.667664, velocity 16.017271 -760.735168 195.597809
L 05/04/2020 - 21:56:02: "Dean<9><STEAM_1:1:00000004><TERRORIST>" threw molotov [-598 555 322]
L 05/04/2020 - 21:56:04: "Alice<8><STEAM_1:1:00000001><CT>" [-592 77 512] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-493 550 512] with "hkp2000" (damage "23") (damage_armor "0") (health "77") (armor "100") (hitgroup "right leg")
L 05/04/2020 - 21:56:04: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-485 548 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-597 61 512] with "sg556" (damage "29") (damage_armor "0") (health "71") (armor "100") (hitgroup "right arm")
L 05/04/2020 - 21:56:04: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] killed other "func_breakable<565>" [134 316 376] with "aug"
L 05/04/2020 - 21:56:04: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-486 549 512] attacked "Alice<8><STEAM_1:1:00000001><CT>" [-590 81 512] with "sg556" (damage "117") (damage_armor "0") (health "0") (armor "100") (hitgroup "head")
L 05/04/2020 - 21:56:04: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-486 549 512] killed "Alice<8><STEAM_1:1:00000001><CT>" [-590 81 576] with "sg556" (headshot)
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" threw hegrenade [-1041 231 322]
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<427>" [-1116 348 376] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<426>" [-885 348 376] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<241>" [-1204 64 372] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<422>" [-930 113 534] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<420>" [-804 172 534] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<432>" [-724 348 376] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<406>" [-1024 510 540] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<408>" [-1088 510 540] with "hegrenade"
L 05/04/2020 - 21:56:05: "James<3><STEAM_1:0:00000005><TERRORIST>" [-1617 410 409] killed other "func_breakable<409>" [-960 510 540] with "hegrenade"
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [116 820 320] with "aug" (damage "24") (damage_armor "1") (health "76") (armor "98") (hitgroup "chest")
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [115 799 320] with "aug" (damage "24") (damage_armor "1") (health "52") (armor "96") (hitgroup "chest")
L 05/04/2020 - 21:56:05: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-507 553 512] killed other "func_breakable<183>" [-418 588 372] with "inferno"
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [114 792 320] with "aug" (damage "24") (damage_armor "1") (health "28") (armor "94") (hitgroup "chest")
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [113 786 320] with "aug" (damage "24") (damage_armor "1") (health "4") (armor "92") (hitgroup "chest")
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] attacked "Sam<5><STEAM_1:0:00000003><TERRORIST>" [113 779 320] with "aug" (damage "24") (damage_armor "1") (health "0") (armor "90") (hitgroup "chest")
L 05/04/2020 - 21:56:05: "Bob<6><STEAM_1:0:00000002><CT>" [123 -11 320] killed "Sam<5><STEAM_1:0:00000003><TERRORIST>" [113 779 384] with "aug"
L 05/04/2020 - 21:56:07: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-490 726 512] killed other "func_breakable<236>" [-594 466 357] with "inferno"
L 05/04/2020 - 21:56:10: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-17 1022 512] killed other "func_breakable<447>" [14 990 534] with "sg556"
L 05/04/2020 - 21:56:12: "Alice<8><STEAM_1:1:00000001><CT>" threw decoy [-1304 -450 322]
L 05/04/2020 - 21:56:12: "James<3><STEAM_1:0:00000005><TERRORIST>" threw flashbang [-1344 -285 333] flashbang entindex 183)
L 05/04/2020 - 21:56:12: "James<3><STEAM_1:0:00000005><TERRORIST>" blinded for 2.94 by "James<3><STEAM_1:0:00000005><TERRORIST>" from flashbang entindex 183 
L 05/04/2020 - 21:56:12: "Alice<8><STEAM_1:1:00000001><CT>" blinded for 0.84 by "James<3><STEAM_1:0:00000005><TERRORIST>" from flashbang entindex 183 
L 05/04/2020 - 21:56:15: "Bob<6><STEAM_1:0:00000002><CT>" [-106 1424 469] killed other "func_breakable<452>" [-144 1312 534] with "aug"
L 05/04/2020 - 21:56:15: "Bob<6><STEAM_1:0:00000002><CT>" [-114 1424 473] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-144 1298 552] with "aug" (damage "20") (damage_armor "0") (health "57") (armor "100") (hitgroup "left leg")
L 05/04/2020 - 21:56:15: "Bob<6><STEAM_1:0:00000002><CT>" [-116 1423 474] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-147 1287 536] with "aug" (damage "25") (damage_armor "1") (health "32") (armor "98") (hitgroup "chest")
L 05/04/2020 - 21:56:15: "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-162 1273 557] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-103 1419 468] with "sg556" (damage "37") (damage_armor "0") (health "63") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:56:15: "Bob<6><STEAM_1:0:00000002><CT>" [-76 1410 454] attacked "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-165 1270 544] with "aug" (damage "100") (damage_armor "5") (health "0") (armor "92") (hitgroup "head")
L 05/04/2020 - 21:56:15: "Bob<6><STEAM_1:0:00000002><CT>" [-76 1410 454] killed "Dean<9><STEAM_1:1:00000004><TERRORIST>" [-165 1270 608] with "aug" (headshot)
L 05/04/2020 - 21:56:46: "Mark<7><STEAM_1:1:00000006><CT>" triggered "Touched_A_Hostage"
L 05/04/2020 - 21:56:46: "Mark<7><STEAM_1:1:00000006><CT>" [-1298 1125 512] picked up a hostage
L 05/04/2020 - 21:57:09: "James<3><STEAM_1:0:00000005><TERRORIST>" [-362 -2008 273] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-163 -1374 256] with "sg556" (damage "29") (damage_armor "0") (health "34") (armor "100") (hitgroup "left arm")
L 05/04/2020 - 21:57:10: "James<3><STEAM_1:0:00000005><TERRORIST>" [-362 -2008 273] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-173 -1395 256] with "sg556" (damage "29") (damage_armor "0") (health "5") (armor "100") (hitgroup "left arm")
L 05/04/2020 - 21:57:10: "James<3><STEAM_1:0:00000005><TERRORIST>" [-362 -2008 273] attacked "Bob<6><STEAM_1:0:00000002><CT>" [-177 -1405 256] with "sg556" (damage "36") (damage_armor "0") (health "0") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:57:10: "James<3><STEAM_1:0:00000005><TERRORIST>" [-362 -2008 273] killed "Bob<6><STEAM_1:0:00000002><CT>" [-177 -1405 320] with "sg556"
L 05/04/2020 - 21:57:14: "James<3><STEAM_1:0:00000005><TERRORIST>" [-244 -2019 273] attacked "Mark<7><STEAM_1:1:00000006><CT>" [-36 -1320 256] with "sg556" (damage "36") (damage_armor "0") (health "64") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:57:14: "Mark<7><STEAM_1:1:00000006><CT>" [-27 -1351 256] dropped off a hostage
L 05/04/2020 - 21:57:14: "Mark<7><STEAM_1:1:00000006><CT>" triggered "Rescued_A_Hostage"
L 05/04/2020 - 21:57:14: Team "CT" triggered "SFUI_Notice_All_Hostages_Rescued" (CT "1") (T "4")
L 05/04/2020 - 21:57:14: Team "CT" scored "1" with "3" players
L 05/04/2020 - 21:57:14: Team "TERRORIST" scored "4" with "3" players
L 05/04/2020 - 21:57:14: World triggered "Round_End"
L 05/04/2020 - 21:57:29: "Dean<9><STEAM_1:1:00000004>" switched from team <TERRORIST> to <CT>
L 05/04/2020 - 21:57:29: "James<3><STEAM_1:0:00000005>" switched from team <TERRORIST> to <CT>
L 05/04/2020 - 21:57:29: "Sam<5><STEAM_1:0:00000003>" switched from team <TERRORIST> to <CT>
L 05/04/2020 - 21:57:29: "Bob<6><STEAM_1:0:00000002>" switched from team <CT> to <TERRORIST>
L 05/04/2020 - 21:57:29: "Mark<7><STEAM_1:1:00000006>" switched from team <CT> to <TERRORIST>
L 05/04/2020 - 21:57:29: "Alice<8><STEAM_1:1:00000001>" switched from team <CT> to <TERRORIST>
L 05/04/2020 - 21:57:29: Starting Freeze period
L 05/04/2020 - 21:57:31: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:57:32: "Sam<5><STEAM_1:0:00000003><CT>" purchased "item_kevlar"
L 05/04/2020 - 21:57:32: "Dean<9><STEAM_1:1:00000004><CT>" purchased "deagle"
L 05/04/2020 - 21:57:33: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "decoy"
L 05/04/2020 - 21:57:33: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "deagle"
L 05/04/2020 - 21:57:34: "James<3><STEAM_1:0:00000005><CT>" purchased "deagle"
L 05/04/2020 - 21:57:44: World triggered "Round_Start"
L 05/04/2020 - 21:57:45: "Dean<9><STEAM_1:1:00000004><CT>" left buyzone with [ weapon_knife weapon_deagle ]
L 05/04/2020 - 21:57:45: "James<3><STEAM_1:0:00000005><CT>" left buyzone with [ weapon_knife weapon_deagle ]
L 05/04/2020 - 21:57:45: "Sam<5><STEAM_1:0:00000003><CT>" left buyzone with [ weapon_knife weapon_hkp2000 kevlar(100) ]
L 05/04/2020 - 21:57:45: "Bob<6><STEAM_1:0:00000002><TERRORIST>" left buyzone with [ weapon_knife_t weapon_deagle ]
L 05/04/2020 - 21:57:45: "Alice<8><STEAM_1:1:00000001><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_decoy kevlar(100) ]
L 05/04/2020 - 21:57:47: "Mark<7><STEAM_1:1:00000006><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock ]
L 05/04/2020 - 21:57:57: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1416 532 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1427 -707 320] with "glock" (damage "25") (damage_armor "0") (health "75") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:57:57: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1219 567 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1427 -707 320] with "deagle" (damage "45") (damage_armor "0") (health "30") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:57:57: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1219 567 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1435 -708 320] with "deagle" (damage "27") (damage_armor "0") (health "3") (armor "0") (hitgroup "right leg")
L 05/04/2020 - 21:57:58: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1187 578 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1455 -707 320] with "glock" (damage "24") (damage_armor "0") (health "0") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:57:58: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1187 578 512] killed "James<3><STEAM_1:0:00000005><CT>" [-1455 -707 384] with "glock"
L 05/04/2020 - 21:57:58: "Bob<6><STEAM_1:0:00000002><TERRORIST>" assisted killing "James<3><STEAM_1:0:00000005><CT>"
L 05/04/2020 - 21:58:00: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1119 625 512] killed other "func_breakable<419>" [-576 208 534] with "deagle"
L 05/04/2020 - 21:58:01: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1312 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-460 323 512] with "glock" (damage "13") (damage_armor "7") (health "87") (armor "92") (hitgroup "stomach")
L 05/04/2020 - 21:58:01: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1143 662 512] killed other "func_breakable<412>" [-825 510 540] with "deagle"
L 05/04/2020 - 21:58:01: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1143 662 512] killed other "func_breakable<416>" [-551 382 534] with "deagle" (penetrated)
L 05/04/2020 - 21:58:01: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1317 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-460 323 512] with "glock" (damage "10") (damage_armor "5") (health "77") (armor "86") (hitgroup "chest")
L 05/04/2020 - 21:58:02: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1317 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-460 323 512] with "glock" (damage "13") (damage_armor "7") (health "64") (armor "78") (hitgroup "stomach")
L 05/04/2020 - 21:58:02: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1317 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-461 324 512] with "glock" (damage "13") (damage_armor "7") (health "51") (armor "70") (hitgroup "stomach")
L 05/04/2020 - 21:58:02: "Sam<5><STEAM_1:0:00000003><CT>" [-467 335 512] killed other "func_breakable<749>" [-1024 510 540] with "hkp2000"
L 05/04/2020 - 21:58:02: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1317 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-466 334 512] with "glock" (damage "10") (damage_armor "5") (health "41") (armor "64") (hitgroup "chest")
L 05/04/2020 - 21:58:03: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1317 624 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-476 352 512] with "glock" (damage "10") (damage_armor "5") (health "31") (armor "58") (hitgroup "chest")
L 05/04/2020 - 21:58:03: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1321 612 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-500 395 512] with "glock" (damage "13") (damage_armor "7") (health "18") (armor "50") (hitgroup "stomach")
L 05/04/2020 - 21:58:03: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1326 596 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-509 411 512] with "glock" (damage "13") (damage_armor "7") (health "5") (armor "42") (hitgroup "stomach")
L 05/04/2020 - 21:58:04: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1327 594 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-515 425 512] with "glock" (damage "13") (damage_armor "7") (health "0") (armor "34") (hitgroup "stomach")
L 05/04/2020 - 21:58:04: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1327 594 512] killed "Sam<5><STEAM_1:0:00000003><CT>" [-515 425 576] with "glock"
L 05/04/2020 - 21:58:04: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1327 594 512] killed other "func_breakable<415>" [-575 445 534] with "glock"
L 05/04/2020 - 21:58:06: "Dean<9><STEAM_1:1:00000004><CT>" [-124 1356 478] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-630 1337 512] with "deagle" (damage "50") (damage_armor "0") (health "50") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:58:08: "Dean<9><STEAM_1:1:00000004><CT>" [-98 1359 465] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-848 1271 512] with "deagle" (damage "57") (damage_armor "0") (health "0") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:58:08: "Dean<9><STEAM_1:1:00000004><CT>" [-98 1359 465] killed "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-848 1271 576] with "deagle"
L 05/04/2020 - 21:58:11: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1100 1255 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-166 1357 499] with "glock" (damage "27") (damage_armor "0") (health "73") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:58:12: "Dean<9><STEAM_1:1:00000004><CT>" [-152 1358 492] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1100 1255 512] with "deagle" (damage "31") (damage_armor "0") (health "69") (armor "0") (hitgroup "right leg")
L 05/04/2020 - 21:58:12: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1100 1255 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-157 1358 495] with "glock" (damage "22") (damage_armor "0") (health "51") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:58:12: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1100 1255 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-151 1358 491] with "glock" (damage "22") (damage_armor "0") (health "29") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:58:17: "Dean<9><STEAM_1:1:00000004><CT>" [-46 1372 467] killed other "func_breakable<517>" [-471 1444 588] with "deagle"
L 05/04/2020 - 21:58:25: "Dean<9><STEAM_1:1:00000004><CT>" [-484 519 320] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-739 159 320] with "deagle" (damage "60") (damage_armor "2") (health "40") (armor "97") (hitgroup "stomach")
L 05/04/2020 - 21:58:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-732 166 320] killed other "func_breakable<183>" [-418 588 372] with "glock"
L 05/04/2020 - 21:58:26: "Dean<9><STEAM_1:1:00000004><CT>" [-484 519 320] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-729 170 320] with "deagle" (damage "49") (damage_armor "1") (health "0") (armor "95") (hitgroup "chest")
L 05/04/2020 - 21:58:26: "Dean<9><STEAM_1:1:00000004><CT>" [-484 519 320] killed "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-729 170 366] with "deagle"
L 05/04/2020 - 21:59:22: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1442 562 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-574 601 512] with "glock" (damage "22") (damage_armor "0") (health "7") (armor "0") (hitgroup "chest")
L 05/04/2020 - 21:59:23: "Dean<9><STEAM_1:1:00000004><CT>" [-567 587 512] killed other "func_breakable<375>" [-1917 480 566] with "deagle"
L 05/04/2020 - 21:59:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1425 554 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-567 587 512] with "glock" (damage "28") (damage_armor "0") (health "0") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 21:59:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1425 554 512] killed "Dean<9><STEAM_1:1:00000004><CT>" [-567 587 576] with "glock"
L 05/04/2020 - 21:59:23: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "4") (T "2")
L 05/04/2020 - 21:59:23: Team "CT" scored "4" with "3" players
L 05/04/2020 - 21:59:23: Team "TERRORIST" scored "2" with "3" players
L 05/04/2020 - 21:59:23: World triggered "Round_End"
L 05/04/2020 - 21:59:30: Starting Freeze period
L 05/04/2020 - 21:59:32: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "sg556"
L 05/04/2020 - 21:59:33: "Sam<5><STEAM_1:0:00000003><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:59:35: "James<3><STEAM_1:0:00000005><CT>" purchased "ssg08"
L 05/04/2020 - 21:59:36: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "p90"
L 05/04/2020 - 21:59:36: "Dean<9><STEAM_1:1:00000004><CT>" purchased "deagle"
L 05/04/2020 - 21:59:37: "James<3><STEAM_1:0:00000005><CT>" purchased "flashbang"
L 05/04/2020 - 21:59:37: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "item_kevlar"
L 05/04/2020 - 21:59:38: "Dean<9><STEAM_1:1:00000004><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 21:59:39: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "decoy"
L 05/04/2020 - 21:59:39: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "ak47"
L 05/04/2020 - 21:59:41: "Sam<5><STEAM_1:0:00000003><CT>" purchased "deagle"
L 05/04/2020 - 21:59:43: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 21:59:45: World triggered "Round_Start"
L 05/04/2020 - 21:59:45: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-560 1889 512] killed other "func_breakable<523>" [-350 1724 588] with "glock"
L 05/04/2020 - 21:59:46: "Alice<8><STEAM_1:1:00000001><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_p90 weapon_decoy kevlar(100) ]
L 05/04/2020 - 21:59:46: "James<3><STEAM_1:0:00000005><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_ssg08 weapon_flashbang ]
L 05/04/2020 - 21:59:46: "Dean<9><STEAM_1:1:00000004><CT>" left buyzone with [ weapon_knife weapon_deagle kevlar(100) helmet ]
L 05/04/2020 - 21:59:47: "Bob<6><STEAM_1:0:00000002><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 ]
L 05/04/2020 - 21:59:47: "Mark<7><STEAM_1:1:00000006><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_ak47 kevlar(100) helmet ]
L 05/04/2020 - 21:59:48: "Sam<5><STEAM_1:0:00000003><CT>" left buyzone with [ weapon_knife weapon_deagle kevlar(100) helmet ]
L 05/04/2020 - 21:59:48: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-323 1461 512] killed other "func_breakable<518>" [-350 1444 588] with "glock"
L 05/04/2020 - 21:59:50: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-931 1347 512] killed other "func_breakable<407>" [-1152 510 540] with "decoy"
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] killed other "func_breakable<565>" [134 316 376] with "sg556"
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [159 229 320] with "sg556" (damage "18") (damage_armor "0") (health "82") (armor "100") (hitgroup "chest")
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [161 239 320] with "sg556" (damage "28") (damage_armor "0") (health "54") (armor "100") (hitgroup "chest")
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [178 235 320] with "sg556" (damage "36") (damage_armor "0") (health "18") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [187 231 320] with "sg556" (damage "36") (damage_armor "0") (health "0") (armor "100") (hitgroup "stomach")
L 05/04/2020 - 21:59:55: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-93 1078 512] killed "Dean<9><STEAM_1:1:00000004><CT>" [187 231 384] with "sg556"
L 05/04/2020 - 21:59:55: "James<3><STEAM_1:0:00000005><CT>" threw flashbang [-1315 -76 430] flashbang entindex 270)
L 05/04/2020 - 21:59:55: "James<3><STEAM_1:0:00000005><CT>" blinded for 4.22 by "James<3><STEAM_1:0:00000005><CT>" from flashbang entindex 270 
L 05/04/2020 - 22:00:09: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw decoy [-1184 127 322]
L 05/04/2020 - 22:00:22: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1643 586 458] attacked "James<3><STEAM_1:0:00000005><CT>" [-1703 596 428] with "ak47" (damage "35") (damage_armor "0") (health "65") (armor "0") (hitgroup "chest")
L 05/04/2020 - 22:00:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1685 591 438] attacked "James<3><STEAM_1:0:00000005><CT>" [-1730 598 424] with "ak47" (damage "44") (damage_armor "0") (health "21") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:00:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1699 593 430] attacked "James<3><STEAM_1:0:00000005><CT>" [-1731 598 424] with "ak47" (damage "35") (damage_armor "0") (health "0") (armor "0") (hitgroup "chest")
L 05/04/2020 - 22:00:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1699 593 430] killed "James<3><STEAM_1:0:00000005><CT>" [-1731 598 488] with "ak47"
L 05/04/2020 - 22:00:23: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1773 601 424] killed other "func_breakable<78>" [-1917 576 461] with "ak47"
L 05/04/2020 - 22:00:24: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<422>" [-930 113 534] with "p90"
L 05/04/2020 - 22:00:24: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<420>" [-804 172 534] with "p90"
L 05/04/2020 - 22:00:24: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<424>" [-740 178 534] with "p90"
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-562 171 512] with "p90" (damage "17") (damage_armor "3") (health "83") (armor "96") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-556 172 512] with "p90" (damage "17") (damage_armor "3") (health "66") (armor "92") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-553 174 512] with "p90" (damage "17") (damage_armor "3") (health "49") (armor "88") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<747>" [-1088 510 540] with "p90"
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-548 190 512] with "p90" (damage "17") (damage_armor "3") (health "32") (armor "84") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-544 194 512] with "p90" (damage "17") (damage_armor "3") (health "15") (armor "80") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<748>" [-960 510 540] with "p90" (penetrated)
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-534 201 512] with "p90" (damage "17") (damage_armor "3") (health "0") (armor "76") (hitgroup "chest")
L 05/04/2020 - 22:00:25: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed "Sam<5><STEAM_1:0:00000003><CT>" [-534 201 576] with "p90"
L 05/04/2020 - 22:00:25: Team "TERRORIST" triggered "SFUI_Notice_Terrorists_Win" (CT "4") (T "3")
L 05/04/2020 - 22:00:25: Team "CT" scored "4" with "3" players
L 05/04/2020 - 22:00:25: Team "TERRORIST" scored "3" with "3" players
L 05/04/2020 - 22:00:25: World triggered "Round_End"
L 05/04/2020 - 22:00:26: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-432 80 512] killed other "func_breakable<754>" [-825 510 540] with "p90"
L 05/04/2020 - 22:00:29: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-795 565 512] killed other "func_breakable<749>" [-896 510 540] with "sg556"
L 05/04/2020 - 22:00:29: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-839 577 512] killed other "func_breakable<406>" [-1024 510 540] with "sg556"
L 05/04/2020 - 22:00:30: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-970 619 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-1371 540 512] with "sg556" (damage "7") (damage_armor "0") (health "93") (armor "100") (hitgroup "right leg")
L 05/04/2020 - 22:00:30: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-992 623 512] killed other "func_breakable<404>" [-1345 510 540] with "sg556"
L 05/04/2020 - 22:00:30: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-1039 617 512] killed other "func_breakable<405>" [-1216 510 540] with "sg556"
L 05/04/2020 - 22:00:32: Starting Freeze period
L 05/04/2020 - 22:00:35: "Sam<5><STEAM_1:0:00000003><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 22:00:35: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 22:00:35: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 22:00:36: "Dean<9><STEAM_1:1:00000004><CT>" purchased "aug"
L 05/04/2020 - 22:00:36: "James<3><STEAM_1:0:00000005><CT>" purchased "famas"
L 05/04/2020 - 22:00:36: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "hegrenade"
L 05/04/2020 - 22:00:36: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "smokegrenade"
L 05/04/2020 - 22:00:37: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 22:00:37: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "molotov"
L 05/04/2020 - 22:00:38: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "smokegrenade"
L 05/04/2020 - 22:00:38: "James<3><STEAM_1:0:00000005><CT>" purchased "flashbang"
L 05/04/2020 - 22:00:39: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "tec9"
L 05/04/2020 - 22:00:39: "James<3><STEAM_1:0:00000005><CT>" purchased "flashbang"
L 05/04/2020 - 22:00:39: "Sam<5><STEAM_1:0:00000003><CT>" purchased "bizon"
L 05/04/2020 - 22:00:43: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "taser"
L 05/04/2020 - 22:00:47: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "molotov"
L 05/04/2020 - 22:00:47: World triggered "Round_Start"
L 05/04/2020 - 22:00:48: "Bob<6><STEAM_1:0:00000002><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_smokegrenade kevlar(100) helmet ]
L 05/04/2020 - 22:00:48: "Dean<9><STEAM_1:1:00000004><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_aug ]
L 05/04/2020 - 22:00:49: "Alice<8><STEAM_1:1:00000001><TERRORIST>" left buyzone with [ weapon_knife_t weapon_tec9 weapon_p90 weapon_hegrenade weapon_smokegrenade weapon_flashbang weapon_molotov weapon_taser kevlar(100) helmet ]
L 05/04/2020 - 22:00:49: "Sam<5><STEAM_1:0:00000003><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_bizon kevlar(100) helmet ]
L 05/04/2020 - 22:00:49: "James<3><STEAM_1:0:00000005><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_famas weapon_flashbang ]
L 05/04/2020 - 22:00:50: "Mark<7><STEAM_1:1:00000006><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_ak47 weapon_molotov kevlar(100) helmet ]
L 05/04/2020 - 22:00:56: Molotov projectile spawned at -1126.669800 652.284607 579.673706, velocity 431.777069 -495.560455 153.666504
L 05/04/2020 - 22:00:57: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw molotov [-574 18 514]
L 05/04/2020 - 22:00:58: "Bob<6><STEAM_1:0:00000002><TERRORIST>" threw smokegrenade [-1285 -510 322]
L 05/04/2020 - 22:00:58: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1112 706 512] killed other "func_breakable<458>" [-676 -58 568] with "inferno"
L 05/04/2020 - 22:00:58: "James<3><STEAM_1:0:00000005><CT>" threw flashbang [-1203 -207 341] flashbang entindex 407)
L 05/04/2020 - 22:00:59: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1123 650 512] killed other "func_breakable<418>" [-568 258 534] with "inferno"
L 05/04/2020 - 22:00:59: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1123 650 512] killed other "func_breakable<419>" [-576 208 534] with "inferno"
L 05/04/2020 - 22:00:59: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1123 650 512] killed other "func_breakable<421>" [-609 190 534] with "inferno"
L 05/04/2020 - 22:01:01: "Sam<5><STEAM_1:0:00000003><CT>" [-1039 -193 512] killed other "func_breakable<454>" [-676 -198 568] with "bizon"
L 05/04/2020 - 22:01:01: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw hegrenade [-1405 -231 328]
L 05/04/2020 - 22:01:04: "Dean<9><STEAM_1:1:00000004><CT>" [172 -5 320] killed other "func_breakable<565>" [134 316 376] with "aug"
L 05/04/2020 - 22:01:04: "Dean<9><STEAM_1:1:00000004><CT>" [172 -5 320] killed other "func_breakable<447>" [14 990 534] with "aug" (penetrated)
L 05/04/2020 - 22:01:04: "Dean<9><STEAM_1:1:00000004><CT>" [165 -6 320] killed other "func_breakable<448>" [78 990 534] with "aug"
L 05/04/2020 - 22:01:04: "Dean<9><STEAM_1:1:00000004><CT>" [155 -7 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [24 1104 512] with "aug" (damage "30") (damage_armor "1") (health "70") (armor "98") (hitgroup "stomach")
L 05/04/2020 - 22:01:05: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-8 1101 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [139 -9 320] with "sg556" (damage "21") (damage_armor "0") (health "79") (armor "0") (hitgroup "left leg")
L 05/04/2020 - 22:01:05: "Dean<9><STEAM_1:1:00000004><CT>" [129 -10 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-25 1087 512] with "aug" (damage "24") (damage_armor "1") (health "46") (armor "96") (hitgroup "chest")
L 05/04/2020 - 22:01:05: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-34 1082 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [128 -10 320] with "sg556" (damage "12") (damage_armor "0") (health "67") (armor "0") (hitgroup "head")
L 05/04/2020 - 22:01:05: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-41 1081 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [126 -10 320] with "sg556" (damage "28") (damage_armor "0") (health "39") (armor "0") (hitgroup "chest")
L 05/04/2020 - 22:01:06: "Dean<9><STEAM_1:1:00000004><CT>" [121 -11 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-53 1081 512] with "aug" (damage "20") (damage_armor "0") (health "26") (armor "96") (hitgroup "left leg")
L 05/04/2020 - 22:01:06: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-61 1080 512] killed other "func_breakable<567>" [64 316 440] with "sg556"
L 05/04/2020 - 22:01:06: "Dean<9><STEAM_1:1:00000004><CT>" [117 -12 320] killed other "func_breakable<446>" [-50 990 534] with "aug"
L 05/04/2020 - 22:01:06: "Dean<9><STEAM_1:1:00000004><CT>" [117 -12 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-62 1080 512] with "aug" (damage "18") (damage_armor "1") (health "8") (armor "94") (hitgroup "stomach")
L 05/04/2020 - 22:01:06: "Dean<9><STEAM_1:1:00000004><CT>" [115 -12 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-66 1080 512] with "aug" (damage "30") (damage_armor "1") (health "0") (armor "92") (hitgroup "stomach")
L 05/04/2020 - 22:01:06: "Dean<9><STEAM_1:1:00000004><CT>" [115 -12 320] killed "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-66 1080 576] with "aug"
L 05/04/2020 - 22:01:06: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw flashbang [-1446 -135 439] flashbang entindex 219)
L 05/04/2020 - 22:01:17: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-585 681 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-432 142 512] with "ak47" (damage "26") (damage_armor "0") (health "74") (armor "100") (hitgroup "left leg")
L 05/04/2020 - 22:01:17: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-585 681 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-432 154 512] with "ak47" (damage "34") (damage_armor "4") (health "40") (armor "95") (hitgroup "stomach")
L 05/04/2020 - 22:01:17: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-585 681 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-432 162 512] with "ak47" (damage "27") (damage_armor "3") (health "13") (armor "91") (hitgroup "chest")
L 05/04/2020 - 22:01:17: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-585 681 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [-433 169 512] with "ak47" (damage "109") (damage_armor "15") (health "0") (armor "75") (hitgroup "head")
L 05/04/2020 - 22:01:17: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-585 681 512] killed "Sam<5><STEAM_1:0:00000003><CT>" [-433 169 576] with "ak47" (headshot)
L 05/04/2020 - 22:01:21: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw smokegrenade [-478 91 514]
L 05/04/2020 - 22:01:22: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1799 439 424] attacked "James<3><STEAM_1:0:00000005><CT>" [-1453 372 327] with "p90" (damage "23") (damage_armor "0") (health "77") (armor "0") (hitgroup "chest")
L 05/04/2020 - 22:01:22: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1801 434 424] attacked "James<3><STEAM_1:0:00000005><CT>" [-1467 374 334] with "p90" (damage "29") (damage_armor "0") (health "48") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:01:22: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1802 431 424] attacked "James<3><STEAM_1:0:00000005><CT>" [-1470 373 335] with "p90" (damage "29") (damage_armor "0") (health "19") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:01:22: "James<3><STEAM_1:0:00000005><CT>" [-1476 371 338] killed other "func_breakable<76>" [-1917 480 461] with "famas"
L 05/04/2020 - 22:01:23: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1802 430 424] attacked "James<3><STEAM_1:0:00000005><CT>" [-1473 372 337] with "p90" (damage "23") (damage_armor "0") (health "0") (armor "0") (hitgroup "chest")
L 05/04/2020 - 22:01:23: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1802 430 424] killed "James<3><STEAM_1:0:00000005><CT>" [-1473 372 398] with "p90"
L 05/04/2020 - 22:01:31: Molotov projectile spawned at -448.995239 480.331512 578.219604, velocity -154.905502 -650.466003 92.321304
L 05/04/2020 - 22:01:32: "Mark<7><STEAM_1:1:00000006><TERRORIST>" threw molotov [-625 389 322]
L 05/04/2020 - 22:01:33: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-648 557 512] killed other "func_breakable<431>" [-724 356 376] with "inferno"
L 05/04/2020 - 22:01:33: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-648 557 512] killed other "func_breakable<432>" [-724 348 376] with "inferno"
L 05/04/2020 - 22:01:37: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-712 592 512] killed other "func_breakable<236>" [-594 466 357] with "inferno"
L 05/04/2020 - 22:01:38: "Dean<9><STEAM_1:1:00000004><CT>" [-179 930 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-591 672 512] with "aug" (damage "30") (damage_armor "1") (health "70") (armor "98") (hitgroup "stomach")
L 05/04/2020 - 22:01:38: "Dean<9><STEAM_1:1:00000004><CT>" [-183 936 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-583 693 512] with "aug" (damage "24") (damage_armor "1") (health "46") (armor "96") (hitgroup "chest")
L 05/04/2020 - 22:01:38: "Dean<9><STEAM_1:1:00000004><CT>" [-191 949 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-582 704 512] with "aug" (damage "24") (damage_armor "1") (health "22") (armor "94") (hitgroup "chest")
L 05/04/2020 - 22:01:39: "Dean<9><STEAM_1:1:00000004><CT>" [-195 956 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-581 709 512] with "aug" (damage "99") (damage_armor "5") (health "0") (armor "88") (hitgroup "head")
L 05/04/2020 - 22:01:39: "Dean<9><STEAM_1:1:00000004><CT>" [-195 956 512] killed "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-581 709 576] with "aug" (headshot)
L 05/04/2020 - 22:01:40: "Dean<9><STEAM_1:1:00000004><CT>" [-217 1075 512] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-499 1260 512] with "aug" (damage "31") (damage_armor "1") (health "69") (armor "98") (hitgroup "stomach")
L 05/04/2020 - 22:01:40: "Dean<9><STEAM_1:1:00000004><CT>" [-218 1074 512] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-478 1249 512] with "aug" (damage "31") (damage_armor "1") (health "38") (armor "96") (hitgroup "stomach")
L 05/04/2020 - 22:01:40: "Dean<9><STEAM_1:1:00000004><CT>" [-221 1070 512] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-472 1246 512] with "aug" (damage "31") (damage_armor "1") (health "7") (armor "94") (hitgroup "stomach")
L 05/04/2020 - 22:01:40: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-468 1244 512] attacked "Dean<9><STEAM_1:1:00000004><CT>" [-218 1075 512] with "p90" (damage "29") (damage_armor "0") (health "10") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:01:40: "Dean<9><STEAM_1:1:00000004><CT>" [-222 1068 512] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-467 1243 512] with "aug" (damage "99") (damage_armor "5") (health "0") (armor "88") (hitgroup "head")
L 05/04/2020 - 22:01:40: "Dean<9><STEAM_1:1:00000004><CT>" [-222 1068 512] killed "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-467 1243 576] with "aug" (headshot)
L 05/04/2020 - 22:01:40: Team "CT" triggered "SFUI_Notice_CTs_Win" (CT "5") (T "3")
L 05/04/2020 - 22:01:40: Team "CT" scored "5" with "3" players
L 05/04/2020 - 22:01:40: Team "TERRORIST" scored "3" with "3" players
L 05/04/2020 - 22:01:40: World triggered "Round_End"
L 05/04/2020 - 22:01:47: Starting Freeze period
L 05/04/2020 - 22:01:49: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "sg556"
L 05/04/2020 - 22:01:50: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 22:01:51: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "hegrenade"
L 05/04/2020 - 22:01:51: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "smokegrenade"
L 05/04/2020 - 22:01:51: "Dean<9><STEAM_1:1:00000004><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 22:01:51: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "molotov"
L 05/04/2020 - 22:01:51: "Sam<5><STEAM_1:0:00000003><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 22:01:51: "Dean<9><STEAM_1:1:00000004><CT>" purchased "item_defuser"
L 05/04/2020 - 22:01:52: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "decoy"
L 05/04/2020 - 22:01:52: "James<3><STEAM_1:0:00000005><CT>" purchased "famas"
L 05/04/2020 - 22:01:53: "James<3><STEAM_1:0:00000005><CT>" purchased "item_assaultsuit"
L 05/04/2020 - 22:01:53: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "p90"
L 05/04/2020 - 22:01:53: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "elite"
L 05/04/2020 - 22:01:54: "Bob<6><STEAM_1:0:00000002><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 22:01:54: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "item_assaultsuit"
L 05/04/2020 - 22:01:54: "Sam<5><STEAM_1:0:00000003><CT>" purchased "famas"
L 05/04/2020 - 22:01:55: "Alice<8><STEAM_1:1:00000001><TERRORIST>" purchased "taser"
L 05/04/2020 - 22:01:56: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "molotov"
L 05/04/2020 - 22:01:56: "Mark<7><STEAM_1:1:00000006><TERRORIST>" purchased "flashbang"
L 05/04/2020 - 22:02:02: World triggered "Round_Start"
L 05/04/2020 - 22:02:03: "Bob<6><STEAM_1:0:00000002><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_sg556 weapon_flashbang ]
L 05/04/2020 - 22:02:03: "Dean<9><STEAM_1:1:00000004><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_aug defuser kevlar(100) helmet ]
L 05/04/2020 - 22:02:04: "Sam<5><STEAM_1:0:00000003><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_famas kevlar(100) helmet ]
L 05/04/2020 - 22:02:04: "Mark<7><STEAM_1:1:00000006><TERRORIST>" left buyzone with [ weapon_knife_t weapon_glock weapon_p90 weapon_molotov weapon_flashbang kevlar(100) helmet ]
L 05/04/2020 - 22:02:05: "James<3><STEAM_1:0:00000005><CT>" left buyzone with [ weapon_knife weapon_hkp2000 weapon_famas kevlar(100) helmet ]
L 05/04/2020 - 22:02:06: "Alice<8><STEAM_1:1:00000001><TERRORIST>" left buyzone with [ weapon_knife_t weapon_elite weapon_hegrenade weapon_smokegrenade weapon_molotov weapon_decoy weapon_taser kevlar(100) helmet ]
L 05/04/2020 - 22:02:10: "Bob<6><STEAM_1:0:00000002><TERRORIST>" threw flashbang [114 125 372] flashbang entindex 722)
L 05/04/2020 - 22:02:10: "Dean<9><STEAM_1:1:00000004><CT>" blinded for 1.62 by "Bob<6><STEAM_1:0:00000002><TERRORIST>" from flashbang entindex 722 
L 05/04/2020 - 22:02:10: "Bob<6><STEAM_1:0:00000002><TERRORIST>" blinded for 0.60 by "Bob<6><STEAM_1:0:00000002><TERRORIST>" from flashbang entindex 722 
L 05/04/2020 - 22:02:16: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-114 1041 512] killed other "func_breakable<445>" [-96 990 534] with "sg556"
L 05/04/2020 - 22:02:16: "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-114 1041 512] killed other "func_breakable<565>" [134 316 376] with "sg556"
L 05/04/2020 - 22:02:24: "James<3><STEAM_1:0:00000005><CT>" [-1378 -73 320] killed other "func_breakable<746>" [-1216 510 540] with "famas"
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] killed other "func_breakable<446>" [-50 990 534] with "aug"
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-94 1046 512] with "aug" (damage "20") (damage_armor "0") (health "80") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-94 1046 512] with "aug" (damage "33") (damage_armor "0") (health "47") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-94 1046 512] with "aug" (damage "33") (damage_armor "0") (health "14") (armor "0") (hitgroup "stomach")
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] attacked "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-95 1046 512] with "aug" (damage "20") (damage_armor "0") (health "0") (armor "0") (hitgroup "left leg")
L 05/04/2020 - 22:02:27: "Dean<9><STEAM_1:1:00000004><CT>" [157 -22 320] killed "Bob<6><STEAM_1:0:00000002><TERRORIST>" [-95 1046 576] with "aug"
L 05/04/2020 - 22:02:28: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw hegrenade [-1359 -151 334]
L 05/04/2020 - 22:02:31: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-56 1035 512] killed other "func_breakable<364>" [-16 324 534] with "p90"
L 05/04/2020 - 22:02:31: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-52 1034 512] with "famas" (damage "24") (damage_armor "5") (health "76") (armor "94") (hitgroup "stomach")
L 05/04/2020 - 22:02:31: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-60 1038 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] with "p90" (damage "17") (damage_armor "3") (health "83") (armor "96") (hitgroup "stomach")
L 05/04/2020 - 22:02:31: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-60 1038 512] with "famas" (damage "19") (damage_armor "4") (health "57") (armor "89") (hitgroup "chest")
L 05/04/2020 - 22:02:31: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-67 1044 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] with "p90" (damage "14") (damage_armor "3") (health "69") (armor "92") (hitgroup "right arm")
L 05/04/2020 - 22:02:31: "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-71 1046 512] attacked "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] with "p90" (damage "14") (damage_armor "3") (health "55") (armor "88") (hitgroup "chest")
L 05/04/2020 - 22:02:32: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-87 1058 512] with "famas" (damage "19") (damage_armor "4") (health "38") (armor "84") (hitgroup "chest")
L 05/04/2020 - 22:02:32: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-96 1066 512] with "famas" (damage "19") (damage_armor "4") (health "19") (armor "79") (hitgroup "chest")
L 05/04/2020 - 22:02:32: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] attacked "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-101 1071 512] with "famas" (damage "19") (damage_armor "4") (health "0") (armor "74") (hitgroup "chest")
L 05/04/2020 - 22:02:32: "Sam<5><STEAM_1:0:00000003><CT>" [20 226 512] killed "Mark<7><STEAM_1:1:00000006><TERRORIST>" [-101 1071 576] with "famas"
L 05/04/2020 - 22:02:32: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw smokegrenade [-545 -109 514]
L 05/04/2020 - 22:02:38: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw decoy [1990 1100 -8318]
L 05/04/2020 - 22:02:41: "James<3><STEAM_1:0:00000005><CT>" [-1289 -688 320] killed other "func_breakable<402>" [-1280 510 540] with "famas"
L 05/04/2020 - 22:02:41: "James<3><STEAM_1:0:00000005><CT>" [-1288 -688 320] killed other "func_breakable<745>" [-1345 510 540] with "famas"
L 05/04/2020 - 22:02:42: Molotov projectile spawned at -1353.124390 516.258179 578.677063, velocity -260.962494 -664.164795 111.621262
L 05/04/2020 - 22:02:44: "Alice<8><STEAM_1:1:00000001><TERRORIST>" threw molotov [-1301 -129 322]
L 05/04/2020 - 22:02:46: "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 512] with "famas" (damage "23") (damage_armor "5") (health "77") (armor "94") (hitgroup "stomach")
L 05/04/2020 - 22:02:46: "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 512] with "famas" (damage "18") (damage_armor "4") (health "59") (armor "89") (hitgroup "chest")
L 05/04/2020 - 22:02:46: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] with "elite" (damage "15") (damage_armor "0") (health "85") (armor "100") (hitgroup "right leg")
L 05/04/2020 - 22:02:46: "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 512] attacked "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] with "elite" (damage "15") (damage_armor "0") (health "70") (armor "100") (hitgroup "left leg")
L 05/04/2020 - 22:02:47: "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] attacked "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 512] with "famas" (damage "75") (damage_armor "16") (health "0") (armor "72") (hitgroup "head")
L 05/04/2020 - 22:02:47: "James<3><STEAM_1:0:00000005><CT>" [-1290 -708 320] killed "Alice<8><STEAM_1:1:00000001><TERRORIST>" [-1386 532 558] with "famas" (headshot)
L 05/04/2020 - 22:02:47: Team "CT" triggered "SFUI_Notice_CTs_Win" (CT "6") (T "3")
L 05/04/2020 - 22:02:47: Team "CT" scored "6" with "3" players
L 05/04/2020 - 22:02:47: Team "TERRORIST" scored "3" with "3" players
L 05/04/2020 - 22:02:47: World triggered "Round_End"
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {hsp},	Dean<1>,	VALUE: 55.555557,	POS: 1,	SCORE: 35.432098
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {cashspent},	James<2>,	VALUE: 21850.000000,	POS: 1,	SCORE: 8.158731
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {kills},	Sam<4>,	VALUE: 4.000000,	POS: 3,	SCORE: 1.405896
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {hsp},	Bob<5>,	VALUE: 33.333332,	POS: 1,	SCORE: 18.148148
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {3k},	Mark<6>,	VALUE: 1.000000,	POS: 1,	SCORE: 26.666668
L 05/04/2020 - 22:02:47: ACCOLADE, FINAL: {livetime},	Alice<7>,	VALUE: 332.000000,	POS: 1,	SCORE: 1.837037
L 05/04/2020 - 22:02:47: Game Over: competitive <allmaps> cs_agency score 6:3 after 14 min
)###"sv;

} // namespace csgoprs::log_samples
