#ifndef effect_myreverb_
#define effect_myreverb_
#include "AudioStream.h"
#include "circular_buffer.h"

class AudioEffectIrReverb : public AudioStream
{
public:
       AudioEffectIrReverb(void) : AudioStream(1, inputQueueArray), queue(9000 + 128 - 1) {
           on = false;
       }
       //to start the effect
       void begin(void);
       //called via interrupt
       virtual void update(void);
       //will be useful for when effect not in triangle
       void turnOff(void);
private:
       bool on;
       audio_block_t *inputQueueArray[1];
       circular_buffer queue;
       //AudioFilterFIR filter;
       short Reverb_IR[9000] = {
         0,0,0,0,0,0,0,0,0,0,0,-1,1,-2,1,-1,1,-1,0,0,-1,2,-3,4,-6,7,-7,6,-5,3,-2,0,2,-7,10,-19,25,-38,36,-39,33,-34,28,-18,11,-48,-337,898,2535,914,121,-1273,-850,-312,-31,3,-12,3,-14,8,-7,0,3,-9,13,-11,13,-6,3,9,-18,40,-58,96,-128,102,-175,244,111,51,-353,-862,-307,963,1017,-69,-101,-298,1529,283,-829,1270,2659,1672,491,29,-203,1077,2385,2080,1132,530,447,1171,1282,256,-1623,-2401,-367,119,-146,-498,-3256,-3479,-2026,-1175,21,908,1099,1248,1201,263,-1728,-575,1627,-2688,-1379,-2013,-2339,-811,-1522,-3783,-3744,-3790,1058,737,-3575,-2552,-2373,-217,-1832,-1234,-2542,-2175,2696,-865,307,-488,-230,5290,6888,2111,-3449,-5214,-5971,-4409,2650,6582,-532,9812,5269,3920,4873,247,-1716,598,7197,7497,2664,3319,689,1769,1181,-1650,1273,4979,850,-2441,-2122,-3015,-4091,-428,3598,716,-3341,-3390,1589,-2869,-1521,-1799,-4468,-4981,-2549,190,-725,-7856,-2823,-3040,-940,-145,-2318,5996,13229,7319,-839,-263,5040,12386,7680,-6767,-74,-2056,-9991,-1251,9502,7684,-1817,-4436,1269,1658,-2156,386,-1794,-710,1751,495,1335,-244,-496,1529,-1111,-6196,-2299,-2310,-4580,-963,-1637,684,-2851,-4794,-2101,1322,2894,3131,2402,2415,1548,62,-2943,3293,2713,1566,482,-931,-658,-376,-3976,-5934,2524,4129,-1688,-34,-2872,-2641,-127,1322,1799,3304,3700,-2499,2161,3652,791,-6701,-5677,3178,1245,-5104,-7091,-4630,955,3141,7411,-3351,-1510,-2252,1287,1035,-1678,2686,3777,-1904,-2150,-1225,690,2033,2028,1561,4482,3790,765,-1301,-353,1163,337,-1137,-2658,-5259,2899,4037,-136,1278,1225,771,-1061,-1702,-1385,-3535,-357,-3309,-1290,3711,2964,6810,744,-1499,1275,3711,2730,4,2014,2766,3512,-3258,1981,2838,-1184,-1564,-2362,-1855,1392,1887,-1318,-2626,48,-571,-249,-140,2748,2157,514,-97,46,181,-244,-326,218,296,360,-156,302,1440,963,377,337,678,1381,608,152,-425,900,-1136,-923,-147,316,499,1167,999,-418,187,918,156,167,-188,142,-122,-455,-158,295,33,215,1734,729,-223,-923,581,1129,762,271,1279,211,-1717,-347,974,-2318,1384,2701,98,1555,-24,563,2345,3370,1551,-2742,-4066,403,-34,883,-984,-1685,-2046,-1110,2302,1723,-1487,-1773,439,1932,4363,3537,578,-3073,36,1641,227,2683,2297,-1622,-2128,-648,-761,3392,1600,1240,1445,-2638,-1300,-2429,-2662,-1315,-70,364,-2931,641,1451,1580,-2372,-265,-85,67,142,1669,3341,2278,304,-1594,-3369,67,1674,1498,3110,1929,840,30,-898,-228,1936,2604,1758,737,-1446,1263,1320,-418,-383,-260,-143,-47,-778,774,3173,2032,320,589,1952,925,-295,-185,467,819,634,43,492,-821,-380,-2576,453,931,443,660,719,-60,-1595,-2502,-121,-967,218,733,-120,1108,-175,997,1626,-256,-980,-28,-1019,780,-247,-1488,-261,1673,1936,-572,-1590,255,1936,1036,-762,175,-894,956,-3089,-1714,-265,1474,1906,576,39,2057,3245,-719,-2095,-1067,-1091,2595,1062,-273,818,1047,-12,-714,-858,574,1420,-2543,2726,1959,607,497,-851,-1955,63,1773,-133,-412,65,427,1142,-3329,-2120,-429,-1650,-1091,1,-302,-942,-1944,-1243,926,-1443,53,-965,-377,1291,491,386,1849,949,-1929,-1188,268,629,-3904,-2848,716,207,-2997,-4813,-3540,-3117,-4311,-923,-1237,833,-4996,-3110,-2073,-2758,464,1574,-2840,-3237,2175,859,1179,351,3097,771,759,105,336,2062,2521,2061,2262,1449,52,1744,1537,1394,-1459,-2422,-2633,-640,-310,-1568,-1331,310,1283,-1446,-1248,-936,-667,1000,1651,2465,1341,124,-443,-1621,-1553,-1630,-1482,-741,-2570,-2914,-1964,-861,0,747,698,280,618,-617,-2166,-960,229,-181,-890,38,296,518,-238,-2323,-1918,1156,-1885,-1187,-241,-343,-230,342,-1335,-1079,-488,-1058,-113,437,-1606,-530,2046,-259,273,-258,1695,2346,1284,1356,1639,4,375,761,960,-1466,-3137,-1066,-393,850,2062,1179,-470,-792,-872,1590,2126,1111,-14,860,-477,-1337,-2133,-1847,-340,-536,-1953,71,-1013,-3071,-3475,-540,519,912,1197,692,-433,242,3375,3151,1375,3218,-48,354,507,2234,-241,-1858,-1244,-1356,-415,658,1263,3304,-1000,-1041,791,1589,603,-209,238,624,-233,-801,633,845,2880,87,-2557,-696,408,805,738,408,1181,3445,5586,1408,287,-141,566,1037,615,333,693,1505,1722,-411,-3586,-63,-3178,1739,4394,709,1658,3292,3378,2736,1736,461,-700,-1431,1815,1837,-554,1338,1219,610,-282,-1356,-1141,-746,-2787,-2185,463,-570,-254,-753,361,-1659,-2967,-808,1231,1447,1719,-1056,-257,-581,766,-1292,20,1415,1764,644,-1085,-876,1291,1146,117,232,-747,-188,579,-1444,-1928,-1114,1045,2158,134,-468,327,-322,-1299,3194,2247,1410,4023,2362,-1243,-254,1458,49,6824,7736,4549,11238,2068,-8364,-5068,-3196,906,4784,2854,0,-5148,533,2825,1098,3487,2553,-1677,-1482,-3232,-800,2797,-1740,-1403,-4431,130,2574,-6986,-249,2462,-1036,-1831,-2773,-1776,3578,3445,3145,6406,4717,-6145,-4186,-619,-2254,-293,157,-4176,-6651,-5360,-5466,-2586,1764,11274,-3412,-4243,441,368,-1727,-795,988,-1466,-4933,525,-629,1532,-66,5055,-113,1201,4691,3262,-2308,-6006,-3108,-1105,-1787,-913,-1909,948,-1670,2347,2494,1068,868,386,2393,3920,3245,-4729,83,2694,-852,-3305,-6072,-4843,1421,3047,-3622,-5392,-4929,-7291,2869,-1091,1564,-4803,-6829,-3624,125,2022,1064,-1217,95,6380,-2665,-4549,468,-3267,-4189,-1576,965,-784,-3650,-86,3341,6113,-1194,-78,440,1843,1445,1001,-819,-2312,-12,2727,900,4458,-570,-3194,6243,2241,4330,2806,427,2515,4735,3363,1459,-4951,-5665,-223,-329,-5093,-1603,-1586,2304,3999,2052,2045,837,2806,3110,-798,-478,3843,4529,2493,1793,1731,2016,1845,-157,-178,1589,1750,594,-1614,-381,1649,2208,101,-345,895,723,1782,-589,1289,-3580,-1868,-1660,-715,-1863,-3193,-780,1371,911,4075,6518,6625,1249,-4599,-3594,-4394,-1397,816,52,-893,-1187,-7,6337,4420,3708,2191,1879,1602,-2444,-4028,1121,2817,-1112,-208,2615,917,2211,3613,-533,-2979,3,4840,5811,2307,-1026,-1484,-2137,-4367,-2156,-2214,1006,150,1829,3232,-499,-2529,-1137,-1031,-283,3135,-295,-1205,-579,3709,4607,6,-2419,-1856,-1309,-1013,1159,4218,1393,-932,4865,5418,4963,4671,1553,-97,551,3097,4950,1859,3223,-59,-113,533,6271,4096,2248,308,-1224,230,1677,-1244,-2309,977,2961,5163,1023,-8,-1075,-2070,-1969,-2465,-2117,945,725,-117,414,1242,-2147,-3173,-105,89,-696,-2561,-2977,1001,3194,3233,-935,1078,-733,2492,-2601,-4848,-1132,466,-2035,-3190,-1363,1957,4240,-389,-3282,4872,1720,-1761,-377,789,273,1337,2580,-157,-378,-1743,1430,1815,3939,1188,-377,-666,-131,1399,2446,2729,2687,-204,-2345,-228,-2999,-3810,-645,1282,189,-1498,-2037,-1112,1518,933,305,3028,2053,2146,2235,-453,-2640,-424,3353,2688,-1593,-3512,-1127,-1527,446,-2305,-2626,-1332,-1231,-770,62,-272,552,-994,-2666,1056,193,-550,-1312,-1111,249,623,1091,2151,449,278,-162,133,-635,4106,2920,431,-568,149,-660,-2872,-2593,-2762,-1213,-1294,-67,-1314,191,2055,2855,1719,911,-39,-3292,-3832,32,-977,68,-2745,-3890,-1933,-66,-587,-744,-235,-231,1051,-873,-2276,-1850,-1508,3573,422,-2680,-693,-852,-3500,-2699,-2164,-6747,-2966,1171,-1757,-1548,1758,3310,2096,-77,-2947,-4573,-3110,-1860,2392,-3218,-2654,-1648,1226,-1071,1048,5768,4700,-237,-1455,-541,-347,253,1953,-514,-1294,209,-962,-551,1538,1477,-79,349,759,1100,3268,1531,986,1185,476,-674,-1492,-285,2660,3384,574,989,757,-4105,-3597,1743,2112,-509,-1644,505,3195,3185,1247,-1994,-1311,-1274,919,545,1377,2432,2678,3514,2925,231,561,2370,2875,2654,942,985,-3221,-2837,-401,-1048,-1803,-403,-298,-69,-1604,-6381,-2238,-2333,-2182,-971,-1805,-3485,-3121,-136,2191,237,-1890,-2950,-820,-313,902,1207,1135,263,-773,-692,291,612,-315,-1981,-729,-1234,710,587,3812,3302,282,-323,348,229,1997,1989,1572,1611,-3160,-1456,-710,-721,-140,-1098,-3280,-3219,-958,2845,-396,1503,1739,-132,-2217,-1133,600,2315,4135,4172,1830,-342,1014,702,-3400,-937,959,-927,-618,545,1244,1654,244,1295,2673,-1313,192,-643,888,-212,562,2691,1180,-510,1969,-411,-1759,875,3001,630,-3142,-1526,-839,-955,-1717,-1934,-458,-956,-1872,606,149,2231,2785,654,297,-211,-2106,-3532,-3028,-1173,741,-288,-538,-501,-398,1365,-182,-901,491,1155,546,1050,1410,-3020,-2656,-982,791,-416,-1936,-791,-739,-272,2476,3347,690,-365,192,-1854,-592,-1107,-1550,-394,587,1098,246,-655,879,-1506,-460,3646,721,-780,-1617,-1647,-1096,-818,-132,730,-37,-723,1311,2809,4475,3090,-399,-594,551,-536,-97,3050,2962,-492,-457,-112,-525,851,2150,-428,-87,250,-546,257,1947,1124,-591,-3115,-645,771,-848,-2459,-1884,-2454,-1703,297,200,-939,-686,-129,-1809,-239,232,155,-869,-1115,1654,3449,1452,-65,1317,1486,1834,-203,-1546,-1391,-752,-320,399,466,507,1472,1266,538,948,-1207,2579,483,-1217,-1511,-129,1242,923,-636,-1642,-1164,-386,-153,-2684,-306,499,-262,-2534,-759,1759,416,-1607,-2918,-248,-2545,1012,4117,601,-2733,-2896,-1914,-73,871,-908,-1022,2466,1383,1743,457,1236,3131,1688,-386,200,1627,1257,458,543,829,-205,-28,630,1739,89,-90,-391,24,1892,1373,-533,-1514,-3525,-623,2767,602,989,333,123,390,547,367,-2046,-1592,-3226,-2460,-138,1213,1908,675,141,-607,-1067,184,914,2042,3702,2042,-2416,-1993,1459,2181,1696,1956,1044,-1120,-1227,-433,-974,1020,1439,-1447,-2622,-2742,-1324,860,1559,971,626,-389,-339,237,232,-1183,1667,565,-2716,-940,664,-448,-361,-446,1360,1511,-1673,2928,4940,1600,-2040,-76,569,-1252,-2048,-4319,-4815,361,1258,2713,-188,-2772,-3263,-298,1951,830,-186,1388,1476,1062,2596,1677,602,-793,150,1093,720,403,282,-125,753,1977,1233,-208,276,275,-1151,-994,-717,474,1501,470,-508,180,2137,5035,298,-1929,1266,770,89,571,295,-1952,-3828,-1408,-288,-2147,-2161,-2726,1141,3425,1097,-571,-337,-134,1022,3371,1451,-3288,-1915,1691,230,-589,-2062,-2026,-899,422,1342,537,-336,-1917,-3220,-663,-882,982,1960,239,-1842,-1985,-457,2368,6219,4258,-527,378,543,614,-1430,-1381,1817,2197,-1965,-4265,-1512,1890,2906,533,-1785,3869,1904,1143,2100,51,-1557,1131,2420,804,-1516,240,-1318,-659,769,1543,423,-1849,-2880,-1033,1270,127,1924,911,608,2808,1277,-325,385,1089,1021,2485,3320,-1347,-950,-187,-4998,-796,1441,423,440,430,-347,709,2113,-708,-914,-662,-1967,200,107,-3413,-3618,-1747,-72,372,-837,-2621,-2963,-2833,-2302,-996,452,1336,1692,451,-1941,-1239,1095,-1076,-3206,2753,332,-94,66,1999,1070,1065,493,-479,-873,-710,-32,-2316,-3206,-18,-3619,-1796,-2554,178,1854,481,-68,1452,2114,1968,-631,-2206,5,1814,1564,448,-846,449,2674,1375,-2472,-2774,657,2027,2906,4589,1471,1256,1189,881,-418,-1782,-149,2825,1423,1145,832,-1018,1243,1528,-719,-1176,297,887,407,457,-859,-4464,-1695,-2880,-5654,-2719,125,2007,1852,994,635,-131,521,2300,125,757,-500,795,-1163,881,4222,3635,2192,2519,73,716,426,-511,444,1709,841,134,-205,-1428,-89,3849,2649,-660,373,-4528,-3832,3274,2817,-2074,-3417,-1529,-417,-1158,-2346,-2705,-1220,-1738,-2232,-755,332,-1105,-1890,-1907,-836,67,-1195,-2434,-3644,-3747,-302,680,19,1704,-65,-829,-1266,-2575,-2136,-302,2100,3030,1341,-214,-1091,1407,-1211,-1945,-187,2153,3187,28,-2529,-1379,-1689,-1089,-251,281,-1414,-2788,195,2292,620,61,525,3059,1520,813,-1251,938,3681,3554,754,-2164,-2240,598,1844,-1593,-1898,-2311,-724,1730,383,-815,-1809,-3153,-3138,-1438,-148,1047,548,-774,605,2566,114,-2635,-1012,439,254,602,692,87,670,1440,2197,1636,1109,3502,2861,1573,-110,-1558,-508,445,801,-101,449,-349,-2194,-1940,-820,-123,2546,4113,1102,-1381,-1025,-443,2568,3620,-473,1344,863,-2448,-2358,-423,-865,-923,595,-2486,-2377,1029,51,-658,-210,-564,-1421,-1691,-1765,-2442,-2930,-2376,-2050,476,213,1096,358,819,2037,1481,605,275,-861,3124,3838,1947,160,680,1163,2255,2782,1587,132,140,1090,1859,1087,1202,374,-458,1176,42,-873,-1051,-993,-358,367,-313,-1837,1352,-923,1917,-184,-842,-340,-194,686,1687,830,24,1780,111,-627,294,345,-1950,-720,-256,-332,714,1067,-413,-1241,570,2783,-1723,-700,-119,-1091,-903,-685,-707,191,1334,867,-1339,668,-891,1675,-282,-497,1328,1531,804,1231,2054,1732,96,-480,-812,-150,23,-415,-814,133,465,-757,-827,1425,1790,182,1511,3442,1397,-944,-1311,-177,463,257,377,897,317,-1355,-2177,-368,56,-1063,-612,618,736,-408,-1040,-160,613,165,1331,475,1415,3662,2158,1054,202,-746,-507,659,577,-264,750,-278,-1240,-1307,166,507,391,-511,-1125,-162,1214,1312,-1033,44,205,-1097,393,346,1254,734,-467,-1078,-1792,-838,447,1212,113,-230,-1286,-1580,-789,332,1493,1314,-146,27,1380,3156,-239,-2212,659,701,1074,1268,1221,605,-354,-711,-1468,-327,1275,2317,3046,1008,-573,-1304,-1922,-431,861,-1491,-1583,1581,431,-2968,-2259,89,-1,-638,176,724,567,985,891,-312,-1369,-2232,-2258,-161,113,-916,-13,1157,1551,1848,1341,475,-181,599,-1174,-1308,-183,802,1107,496,-139,-24,661,1236,-432,-1097,676,2076,2155,2073,1722,-172,-1264,309,2934,4416,3014,3,-561,346,1091,493,291,362,243,-666,-2553,-3332,-798,-1232,-1103,539,921,573,35,649,1041,565,-110,-42,1592,1608,1542,990,1174,964,297,165,-420,-1039,-365,908,508,-1637,-1882,-1258,-277,-54,-1630,-1899,-546,766,1175,1342,1627,850,-168,69,-220,413,-42,-560,374,828,-335,-1076,-143,302,477,-796,1213,-658,-2266,-896,474,676,-11,-523,355,1711,808,-226,1028,-478,-555,122,1148,757,-902,-2170,-1795,17,1030,-597,-377,-1431,-1162,-840,-193,185,-314,-962,-1590,-1980,139,531,-728,-52,341,353,-1083,-1426,-434,-24,-377,-244,-440,-1848,-2055,-550,1351,2030,211,-747,-649,864,2531,1866,6,-17,-1456,-1658,774,1116,183,472,80,-470,-159,574,1196,936,-775,-952,-89,-1368,189,685,-306,-1191,-914,-632,-1300,-1130,-748,29,2948,1092,-30,183,37,-363,-237,896,1994,943,-1234,-2122,-2949,728,2305,2513,1469,-431,-1420,-1221,186,2357,1106,862,81,583,385,-1035,475,991,351,228,28,-974,-683,2057,-587,-1525,-380,1113,2745,1553,564,-492,-1380,-211,144,-734,1075,1512,661,330,-92,47,-346,838,1513,-203,-326,-798,-574,-450,-693,-730,-396,-398,127,1657,1923,940,1079,545,1055,827,-1331,431,-999,-2792,-2049,-508,643,1384,1101,-136,-700,555,805,-68,-2028,-2594,-668,154,-847,-1538,-1399,-1348,-594,-1442,-2292,-334,293,1675,151,-1333,-1523,-751,921,1938,-58,-1537,-368,2850,-731,-794,813,-307,-2783,-1463,667,-1454,-1492,-455,-1563,267,715,-216,-246,-795,-1070,-608,-1577,-3855,-3755,-3179,-2438,-687,325,1155,285,-209,-1112,527,2758,2551,2393,897,-3103,-2465,1405,2017,-1431,-1523,-440,1319,2916,1696,-1284,-880,606,1124,-1172,-2179,-1791,495,2190,1763,266,-823,-1188,-1147,-1097,-317,-2176,981,849,2074,1872,555,722,1225,325,61,618,-201,-866,-357,280,72,33,498,637,-180,-977,-348,988,1262,646,-853,228,250,-139,-48,574,1405,620,-1669,-1646,-826,-757,-1014,974,1487,-232,-471,2352,3476,1099,-1192,-1361,-164,1461,1192,-658,-1370,-183,313,-376,-569,475,767,-724,-1473,-3581,-2525,1346,105,-183,-134,-620,159,893,539,202,-617,-511,899,201,1851,2644,-235,-298,669,929,101,-870,-380,-1317,434,363,-761,-1428,-609,-115,215,1433,865,-842,380,493,1362,1444,-118,-1376,-1179,152,1498,2107,70,-2609,-1340,1382,-360,-178,2032,9,-1919,-1271,791,-371,-2859,-1696,1550,2277,4169,1672,27,-283,-1308,-1289,-840,-67,149,-19,-473,-1550,-1157,-63,1005,1251,-165,-768,-454,62,393,-546,-1018,1396,2931,881,-919,-324,-117,-1329,-706,279,298,-265,-270,520,690,-861,-982,-805,-994,1315,2074,540,283,316,-667,-1795,-2580,-1839,1085,626,-2505,-975,230,159,-438,-570,-223,243,429,-522,-1760,-452,-1347,-1859,412,1496,-577,-1591,-210,986,884,538,-623,-495,274,1026,1292,845,614,-254,-610,602,2246,1814,-1996,-1969,807,-358,-1331,-1130,-200,866,101,-1750,-3199,-3539,-755,765,-496,-1897,-498,1437,2606,2930,1297,399,1276,1076,-286,-1018,691,418,3429,4250,1913,94,-561,-628,-412,-223,-16,657,-882,-946,-8,308,418,179,-826,-1262,-151,1652,2796,2524,-397,-2299,-3423,-1551,408,45,-383,-974,-1089,-333,109,619,2319,2842,823,-344,-486,-180,2327,2940,960,-875,-1299,-562,943,-218,-1544,158,3366,2723,1009,353,423,188,-398,-731,-672,381,1716,1798,-995,-1130,-159,8,85,-7,-739,-1571,-1824,101,233,519,-892,-1348,-873,-1294,-522,1293,1673,640,859,2122,1363,850,964,699,543,874,1037,408,-255,228,1805,2819,-184,-1426,-891,1603,1580,72,-696,-203,1325,1694,196,1086,749,-2239,266,205,-9,99,-688,-885,-962,-1206,-298,1014,938,194,-858,-409,-1023,-842,-151,351,480,205,424,1226,-753,-1939,-1591,1122,3145,941,-1098,-682,-106,-223,21,116,-542,411,-383,-961,252,1072,774,-139,-282,510,887,-67,-1010,221,516,1825,315,-900,76,217,-449,-500,-243,174,1847,2774,1190,-1116,-912,-1130,-2307,-929,786,279,-1730,-2054,-383,-861,875,4847,1589,86,588,1024,1067,908,539,12,-367,-475,-584,195,2160,1832,642,124,-9,80,-444,-998,-491,435,2030,3261,1248,192,580,1343,868,270,269,1134,1797,844,233,482,-1167,-2524,-193,-107,-428,-73,34,53,722,1625,1789,525,1356,639,-24,-449,-300,-978,-638,674,759,-442,-454,846,1602,603,317,-996,278,951,429,169,-67,-825,-1198,-1259,580,401,-650,-1576,-1095,-285,236,1382,1478,859,1784,1500,1552,-1597,-1840,195,789,-381,-1435,-650,27,-44,441,159,-813,-964,-445,-1035,-905,753,997,-59,-1017,-609,483,324,-41,-358,-1065,939,1786,491,631,600,83,-112,2,395,1477,1746,1131,260,245,-54,1013,913,548,907,1357,1380,817,-815,-1063,-1030,-55,33,199,560,257,-725,-1298,-1152,-1156,-861,158,1179,988,-21,-707,-360,-580,-295,683,1161,1009,198,-606,-320,-294,-1841,-2019,-764,-204,182,-423,-1697,-1332,-379,-814,-167,442,871,270,-85,1021,1728,1099,456,532,79,-876,-199,167,-161,1530,938,294,403,-50,108,1724,2269,1471,1452,1196,1424,1505,556,1152,343,-96,-27,-237,511,1053,-603,593,943,264,-902,-606,612,1398,800,-765,-1492,-492,23,541,745,215,165,820,326,-84,147,789,1383,1365,1078,33,-1647,-2334,-653,683,616,58,-902,-1338,-817,-241,628,1484,1052,1686,651,-217,154,378,391,194,-147,-291,-702,-1941,-1337,533,501,-380,-932,-751,-182,53,-192,-271,-120,-742,-8,-233,-253,-807,-1919,-1023,285,1595,1946,479,-698,647,1092,-268,718,-288,-1850,-2045,-736,780,1329,1146,990,580,-302,-820,-148,211,808,693,320,819,690,-260,-119,973,1277,1441,-1059,-1512,1026,1230,779,179,-338,-888,-1118,-182,710,-821,-972,-118,-129,-915,-1710,-1351,-307,-661,-2138,-2518,-1783,110,182,-474,-47,-486,-219,-530,-607,85,690,558,154,-174,-263,174,995,-149,-33,-52,-144,-254,-626,-847,-549,-578,-251,264,73,352,47,458,687,297,675,1832,1860,653,-695,-462,1134,1480,484,417,228,-204,-21,206,-748,-1455,609,79,-1837,470,2585,846,-679,-418,-325,-1256,-1718,-976,-506,-1005,-1625,-534,-947,-1818,-2149,-1699,-345,844,465,-895,-971,134,265,346,-307,-380,297,561,217,-282,-372,358,1324,791,18,-538,-968,-425,-1299,-518,-23,-384,-283,167,420,1804,1401,-402,-4,-21,-440,-299,874,1229,-557,-1906,-290,1169,1746,807,-10,-45,111,1155,1433,334,-946,-1155,-711,-936,-1010,1145,130,299,739,420,330,-514,-427,995,1273,175,414,681,575,317,831,98,-1074,-502,439,432,-195,-1029,-1060,610,932,1423,1610,678,-223,-535,-436,-96,6,-189,152,-82,-366,-1304,-1295,-947,-684,-39,411,311,-245,-237,1065,985,460,1218,-103,-317,1041,506,-82,167,572,835,805,3,-666,-24,-736,-281,-566,-1706,-1236,-105,898,1027,-224,-637,-939,-2463,-1818,172,349,-557,-659,-400,168,503,36,-261,-791,4,1270,955,-1257,-686,-560,-515,325,902,688,663,505,950,1254,-526,-1874,-343,875,592,-391,-914,-782,-322,500,618,504,-131,-2137,-3026,-1844,-1691,-1838,-876,280,427,395,766,-256,-1659,233,1222,821,85,-318,59,480,187,-402,-1327,-1338,-885,-250,1021,396,157,-210,-115,-249,-1542,-2571,-2171,-1532,126,911,785,777,505,324,-48,397,1200,526,-300,646,-373,-1409,-894,-220,64,-86,260,651,276,-467,-638,-280,-776,-1039,1046,184,102,-938,-1794,-31,1424,500,286,325,293,2559,97,-277,-110,-284,92,227,-615,-1394,-980,-467,-1353,-1429,-629,-1398,-2586,-1699,57,617,503,577,331,-45,914,1800,1268,311,86,-539,-176,122,-1146,-2712,-2575,-1213,-36,488,-652,534,1098,888,-15,-804,158,1107,-52,-1335,-55,1758,1308,884,1985,1372,182,63,129,309,150,-641,-649,-925,-952,-142,-756,-1285,-70,-670,-2237,-1899,-350,259,57,-899,-1156,-456,-229,240,-198,-136,334,724,657,230,26,-32,-1204,69,1223,608,-625,246,-177,-652,102,1426,2235,1807,805,-2100,-1823,-1848,-1196,223,107,-570,-362,3,203,820,-434,-808,402,1165,1152,1362,629,118,-308,-711,-1605,-2877,-1449,289,-45,426,-456,-163,383,241,-482,-1351,-1690,-668,1312,1817,1249,-373,-1436,-1419,-168,308,810,398,-473,5,571,-337,116,822,1637,891,-71,98,139,-260,-613,-755,-465,493,587,681,1041,910,296,-238,-135,798,1767,1547,-378,-2800,-2661,-271,-285,293,50,-330,-146,-403,-9,610,142,163,579,828,682,511,-332,-833,242,518,118,-535,-1243,-917,-273,-290,-711,-158,818,1380,-245,-1419,-1104,-504,-300,-157,-378,-906,-533,467,-101,-27,-1209,-1032,510,978,-108,-908,-492,434,-1040,-1786,-853,-152,196,558,115,-599,-269,1164,2180,1529,79,-1456,-712,238,1860,2173,814,-240,-70,216,-25,273,934,-8,840,241,76,654,731,192,-349,-522,-233,460,784,-251,-138,-143,-97,1087,1119,617,418,623,675,-24,-430,-52,-947,-1107,-385,-87,274,132,-669,-706,278,844,1085,425,-267,904,377,-92,98,389,487,434,187,-109,-152,-547,0,772,594,477,-168,-914,-450,925,1551,832,-199,-1225,-2136,-679,1135,538,625,1019,661,574,1754,2467,934,-387,-183,1604,1733,1019,1250,913,559,-201,-844,-369,556,333,-700,-579,67,-180,148,1483,1601,-85,-1322,-724,121,-35,802,973,-155,202,-164,-443,194,714,-628,-1800,-1085,-315,829,1039,182,727,1162,1733,1194,736,803,583,-46,-217,158,445,-397,511,300,467,1116,1293,1129,568,-326,-1116,-1312,-199,-353,-246,561,685,428,-190,-478,-121,805,1442,1188,1615,1762,1126,1578,796,503,986,873,352,286,466,248,-218,-1239,-1075,-584,-102,-143,-564,-480,-358,333,1498,1526,280,-174,328,1399,1350,-106,-137,-75,-236,-274,-96,93,-34,-585,-585,-771,-1092,461,1029,406,-204,-483,-579,-556,-468,-238,241,501,368,-532,-1378,-510,379,565,-44,-861,-967,-704,-997,-611,-252,40,-323,-76,243,381,735,1111,1104,1007,797,681,750,679,655,793,393,-138,-599,-650,-553,-987,-924,339,596,-306,-479,-1422,-1226,-858,-601,-193,294,539,130,-978,279,637,271,243,320,-330,-1348,-1310,-43,764,174,-64,790,590,-843,-1735,-450,1054,406,-721,-757,-73,543,203,842,971,-137,670,-223,-976,78,204,-416,-241,-226,-503,-176,-94,664,538,-343,-784,-496,-1030,-1787,-827,699,-11,-397,-1387,-1276,568,567,1248,1294,418,222,1131,1728,1139,150,-231,97,-157,-392,86,427,301,-51,74,276,-261,-389,-31,57,356,457,-929,-1497,-654,578,1008,348,-249,104,-566,-97,-713,-569,899,1091,413,-194,-787,-697,433,1172,1062,482,535,602,1113,702,445,844,1223,1369,1224,365,-615,-389,1083,555,767,-1175,-1906,-682,-183,-878,-890,327,1052,37,-680,-1030,50,438,146,-504,-785,-668,-366,-29,324,1210,1260,-36,-115,-615,-345,424,-96,-733,-695,-629,-617,-647,-1037,-1995,-1076,-362,-723,-653,532,1011,210,-491,-379,-234,-131,-162,-93,1194,896,-324,-1881,-1420,-67,353,113,-224,-69,683,744,383,-255,-252,-442,-251,54,253,338,226,699,1225,145,79,692,945,364,30,-139,-533,-664,-222,-11,123,-302,-605,200,785,95,-404,-142,297,519,779,1146,1153,1446,1476,1079,736,478,401,219,273,188,-214,-170,-305,-449,-990,-994,-127,-1080,-465,1283,1230,-8,-190,328,389,332,123,-161,444,-20,-714,-526,-366,-565,-211,619,370,-536,320,77,-689,-1448,-1080,-530,-621,-261,619,792,209,-434,-705,-545,-1162,-1097,-625,-337,508,797,336,134,-86,-1072,-1009,-163,792,1154,169,-937,-1080,-353,472,1058,1491,1470,726,141,790,985,805,-328,-362,264,-93,-958,-829,-69,353,303,-564,-844,140,659,193,-562,-649,-591,-766,-255,510,-70,-57,688,-9,-333,398,529,-280,-691,-462,-420,-87,395,-245,89,-689,-279,540,914,498,17,308,762,182,-394,-280,280,284,-249,-105,735,1034,649,-8,-502,-331,344,803,-238,-1057,-581,-198,-651,-955,-410,42,70,158,-326,-130,485,956,982,631,110,-275,26,81,-444,-636,-643,-1150,-816,332,342,499,406,-348,-199,812,1394,984,324,411,147,-1096,-139,-14,-353,461,1063,374,-828,-1296,-849,-88,547,568,186,544,562,-271,-1143,-1091,-319,218,240,34,-968,-740,524,-244,-611,-488,-494,-329,513,879,77,-229,341,355,-230,-952,-403,-658,-820,-304,1,5,-94,-114,1115,1373,518,33,-976,-777,-369,-493,-837,-508,333,555,-112,-888,-809,-427,147,-164,216,17,-706,-975,-204,1011,1392,829,860,523,-737,-1735,-1069,-984,-802,-309,-91,296,1079,434,-52,504,156,903,697,-104,-414,-410,-31,-25,-1001,-1033,-268,-1201,-1720,-899,-986,-2008,-1928,-1080,-253,87,249,830,459,-111,-298,-709,205,115,-519,-60,207,-157,-71,-92,-1149,-652,-594,-468,211,394,120,-292,-224,-46,-57,132,375,774,454,503,876,613,540,182,121,398,714,793,199,-281,574,1134,388,-42,615,413,-185,-533,-102,293,-632,-636,762,446,-252,-285,-761,-957,-424,586,865,-428,-1822,-954,214,741,434,-265,-97,178,120,-141,-688,-1004,-377,271,-581,-1344,-256,-303,-913,-792,39,746,673,236,-341,-1250,-800,1053,922,707,590,-415,-465,-515,-1063,-1172,-604,-277,-143,257,627,542,1076,938,1250,1006,877,542,-459,-961,-244,129,-466,-27,135,-493,-29,227,197,31,-523,-650,465,236,-648,646,544,-259,-281,-162,-505,-844,-330,689,864,118,-176,-422,-705,-768,194,766,520,-105,-740,-1244,-1101,276,1549,391,624,140,-981,-552,-243,-588,-518,175,366,-160,12,137,-287,-469,-160,250,421,-268,-768,-84,686,266,-53,-450,-1039,-556,458,297,-316,-569,-288,-74,-436,-764,-129,278,-34,26,-596,-676,283,928,635,75,-103,-104,-178,237,786,-374,-236,1096,1088,364,-58,303,807,495,-498,-934,309,1301,627,-166,-211,-910,-1547,-710,602,466,-549,-279,396,-23,-357,6,327,146,-332,-531,-706,-743,-121,299,-562,-666,-193,81,-286,-332,254,65,-149,63,-7,36,561,-254,-185,-265,-244,638,789,489,306,-197,-549,260,678,64,-35,-640,-166,329,147,-710,-1608,-1562,-885,-301,497,19,-309,524,912,309,-511,-776,-421,61,-237,-1063,-764,293,6,-159,343,818,-45,-862,-1011,-904,-509,24,-75,-467,-300,476,913,696,-616,-1006,-464,-206,-502,-702,-449,-4,209,94,18,-576,-807,-484,-678,-639,-231,-31,-293,-518,486,1216,1772,1916,875,-650,-627,-287,-467,-199,821,1057,-69,-853,-1102,-1217,-904,-16,578,667,607,832,805,199,301,376,-230,-590,-543,392,514,-36,-263,32,177,-55,-23,197,-324,-549,-1442,-591,259,5,384,883,734,308,-119,-13,193,82,103,696,956,208,-62,-521,-1317,-1351,-605,-172,133,-579,-1267,344,564,295,513,310,-57,-110,-36,382,433,-24,-139,-14,25,611,1121,1049,690,311,-8,-32,43,-434,-903,-1150,-693,-125,-175,-75,686,1142,538,-218,-148,137,409,113,-247,537,940,1199,797,356,324,99,-214,-636,-1497,-775,349,473,690,709,471,175,105,305,346,-15,-79,-516,577,893,242,3,62,260,440,691,1162,1033,187,349,-44,148,321,-96,-227,-251,-198,86,163,-276,-486,-466,-276,120,790,1018,225,-282,39,402,438,611,465,19,-197,480,530,-412,-129,29,-511,-769,-355,8,28,-98,134,324,392,354,399,492,312,173,386,609,605,432,-131,-250,248,716,535,555,440,-43,-333,-129,-15,-220,68,547,139,80,-73,-192,333,821,482,-111,-142,-123,510,1140,338,-281,-105,35,-316,-586,-753,-873,-593,-304,-199,112,389,-36,-434,-123,-92,-220,22,372,437,342,-392,-699,64,640,682,-42,-127,586,811,575,494,100,-59,174,259,338,425,81,-176,-231,-505,-706,-434,-24,210,-19,-435,-661,-530,-216,-88,-132,-213,-113,212,507,487,101,-654,-297,171,272,-170,-715,-291,246,-7,-513,-613,-413,-546,-573,-174,6,63,6,-50,-353,-474,-229,-16,767,1420,578,384,-85,75,311,431,771,711,7,-219,499,776,217,310,939,687,882,295,-288,-326,-67,73,-331,-871,-516,-768,-560,-598,-285,70,388,413,105,-37,223,201,-62,-58,-318,-156,-81,19,242,170,99,240,120,-100,123,165,85,320,30,-492,-562,-371,-224,-216,-233,-197,-579,-745,-630,-155,78,-353,-539,-557,-500,-326,-42,229,60,-485,-261,-69,129,635,311,-129,-161,-162,-339,-609,-1182,-939,-365,257,551,177,331,581,782,757,626,636,327,-504,-486,-569,-499,112,84,-310,-327,-173,-222,-347,-375,-296,88,-103,-28,279,62,159,-147,-421,-106,481,792,698,717,417,83,594,500,269,81,-253,-558,-519,-101,369,134,-448,-163,28,450,-205,-832,-200,467,380,88,-294,-357,-349,-131,116,377,400,-200,-456,-424,-370,-112,98,-304,-296,-171,34,86,-168,13,-44,95,441,180,-528,-415,-59,-177,-610,-363,281,300,454,562,654,732,440,29,346,519,766,1125,121,-377,-148,-380,-362,203,460,315,285,174,821,1017,704,467,514,110,-23,130,-186,-500,71,-325,-556,-175,-140,-186,-328,-110,216,-15,-443,-398,-214,242,418,145,-242,-60,627,900,703,279,-141,-214,206,538,331,233,-79,-647,-771,-353,48,-94,-270,140,480,-151,-499,-234,55,394,370,34,-435,-871,-877,-465,-161,-209,-555,-1513,-162,676,-136,-16,532,283,-136,185,617,361,345,112,318,174,40,267,-261,-966,-1047,-724,-254,276,55,-117,611,512,0,-42,541,620,436,325,248,298,394,64,437,621,-294,-128,413,450,359,346,266,71,-128,-119,127,220,198,110,238,614,695,463,223,0,-192,-83,-458,-827,-649,-21,89,-239,-366,-422,-239,425,952,752,849,590,5,-27,-428,-150,131,82,-215,-350,-65,219,164,567,576,-101,-337,-125,223,44,-535,-927,-848,-655,-835,-521,-671,-85,1,-798,-496,140,624,830,479,-184,-345,-407,-155,798,628,60,145,130,-97,-47,-51,-302,23,69,-350,-62,-230,-383,-435,-360,-352,-151,435,593,-180,-193,139,401,48,-421,-39,378,-30,-344,33,449,275,-254,-721,-240,426,82,-190,-697,-486,-1,44,165,544,45,-323,182,95,-550,199,531,-245,-609,-368,-431,-675,-314,37,303,921,381,-347,157,347,197,-30,-157,11,268,-65,-906,-972,-4,166,-6,-212,-417,-101,361,197,-249,-47,236,236,139,-286,-26,-47,-61,339,651,667,566,312,458,412,-647,-709,-221,64,304,213,-374,-697,-444,-349,-289,216,435,430,286,133,-4,-268,18,530,399,-93,-157,-404,-128,-11,-176,-463,-506,-424,-276,-101,34,95,15,-300,-445,-325,-40,94,255,147,14,53,118,109,158,177,-149,-338,276,479,74,-386,-14,236,78,115,193,40,785,321,-65,-252,-187,117,-75,-336,-163,-9,-223,-196,18,39,629,246,-363,-452,-557,-521,-70,355,132,-395,-191,245,217,32,-90,-176,-2,367,375,203,287,245,-260,-140,160,153,134,-280,-304,-254,-199,2,102,-36,-78,-525,-932,-302,401,-8,-242,-120,-255,-480,-238,272,309,84,681,826,294,-6,-379,-341,51,359,265,-11,92,640,743,82,-340,-365,-150,153,22,-289,-154,173,109,66,223,241,-404,-567,0,320,214,-243,-681,-702,-511,-623,-649,-411,-460,55,87,13,-11,34,211,540,786,549,-85,-92,-442,-573,-30,371,14,-319,-61,172,-151,-512,-459,-597,-613,-576,-599,-211,-76,-145,11,124,110,359,682,424,-23,-507,41,333,162,11,87,192,172,-10,-332,-440,-6,-41,-257,161,-199,-706,-535,-46,285,342,105,-290,-590,-254,396,557,357,336,118,-312,-479,-237,94,276,115,-325,-408,-429,81,538,315,145,109,81,180,216,-77,-250,343,428,-161,-222,-36,-88,-74,-4,-152,-294,-68,340,201,102,420,424,215,-18,-89,-44,4,304,1075,1346,223,200,161,-2,224,83,-69,-26,62,-9,-297,-354,-141,-358,60,122,315,497,396,503,506,138,168,583,421,-135,-76,-142,-298,-87,-35,-99,-176,-247,-187,-5,60,71,-182,-199,25,165,91,339,630,418,154,489,482,-23,-25,-147,-62,-22,-227,-317,-227,-27,186,131,-301,-434,108,383,-20,-552,-403,256,287,-44,155,564,482,599,892,257,101,53,83,169,138,66,21,-29,-5,35,-95,-252,-31,276,391,114,-225,-292,-97,212,483,420,187,124,149,621,221,-420,-238,-19,-270,-470,-266,-3,-137,-151,-119,-141,-40,-154,-243,-231,-74,95,68,-15,80,-100,-213,45,79,133,212,35,-202,-131,126,164,84,91,-116,-268,11,125,19,-179,-127,134,236,-26,-458,-392,63,333,552,547,316,-106,-138,221,548,532,144,116,562,-210,-131,403,385,56,-246,-157,71,-105,-546,-713,-609,-381,150,249,104,-15,126,160,19,34,166,116,234,7,-7,31,31,-30,64,230,319,448,586,372,146,-270,-393,-167,-83,218,302,50,-59,22,-88,-297,-219,59,-240,-272,-61,52,151,18,-60,33,65,12,56,52,-129,406,459,-229,-329,-106,-20,-88,-124,-108,-167,-130,191,422,68,-29,299,682,719,404,78,-59,-95,55,54,82,-16,-98,-193,-457,-379,60,207,-14,-14,14,251,691,442,348,327,167,11,94,369,466,282,255,222,192,207,113,-188,-168,-148,-234,-175,-13,-15,12,406,601,605,719,72,-160,-70,145,287,131,-190,-263,-131,66,529,491,48,97,50,-77,-259,-432,-462,-403,-407,-197,159,-2,-259,-207,-102,95,135,1,-71,-11,143,422,0,-179,120,-21,-182,-56,-187,-267,125,484,359,355,-164,-452,123,108,-188,-287,-242,-144,54,230,135,-79,-53,-207,-228,-44,10,76,156,138,56,-186,-448,-144,153,-132,-98,0,-28,-300,-329,-170,-79,44,323,436,205,150,206,118,79,54,-32,23,45,-58,8,240,53,-31,181,294,213,213,78,-269,-372,-282,-239,-58,205,-119,-335,205,159,6,171,205,103,-58,-134,-33,27,-32,-169,-122,17,186,208,-113,-291,-327,-286,-125,-16,-80,-387,-344,-193,-187,-108,18,85,34,-84,-101,-66,-299,-348,138,484,278,-48,-11,135,171,238,291,101,-63,264,300,-52,-37,138,354,201,-36,14,201,306,370,206,95,117,-30,0,-92,-62,59,80,103,191,186,137,-60,-266,-753,-527,-220,-48,204,145,-162,-180,150,214,-207,-249,118,226,113,50,62,171,259,157,-59,-115,-4,43,7,13,62,83,20,-2,74,194,323,287,-203,-367,-51,78,246,199,-18,-65,7,65,172,290,147,-55,-42,-90,-133,-271,-323,-271,-312,-306,-37,197,43,68,240,-64,-181,-228,-199,-75,-56,-153,-176,-111,-124,-89,113,-219,-121,129,173,107,-261,-328,56,199,-166,-324,-203,-160,-31,-95,29,183,174,-24,-294,-413,-216,152,241,-17,-366,-114,186,138,155,295,140,-97,13,157,23,84,121,-86,122,282,257,299,273,249,302,263,183,103,18,-35,177,172,101,-72,-335,-364,-221,-150,55,159,-148,-153,-72,43,33,-66,-98,-96,10,194,207,217,269,286,300,29,-281,-82,158,205,178,88,-98,-197,-278,-232,-185,-100,-131,-209,-83,63,118,72,-29,24,168,-3,-105,-63,-201,-216,-279,-361,-261,-32,116,126,-14,-49,-140,-116,-44,70,196,188,108,113,246,357,236,32,156,323,197,60,32,-35,13,102,53,-10,55,-11,-194,-335,-45,72,-50,-3,139,163,78,-2,-66,-53,211,489,260,-80,-157,-260,-401,-407,-298,-153,-28,-134,-205,-105,11,138,38,26,87,-8,-115,-135,-221,-214,69,74,-100,-120,-126,-44,-119,-180,-58,8,-50,71,42,-55,-42,-253,-150,-66,-35,-14,20,40,9,-43,-31,26,-49,-46,-81,-159,-77,25,-43,-166,-115,29,6,0,147,124,-35,-15,0,-118,-167,-56,17,-59,-104,-35,12,36,114,29,-93,-87,52,168,131,-8,-48,114,147,11,234,377,167,42,42,74,84,125,221,157,-149,-153,54,11,-88,-84,132,232,50,-161,-201,-262,-445,-383,-74,112,175,36,-161,-193,-89,11,46,3,-85,-87,-43,-55,-70,77,0,-107,-107,-96,-73,66,143,-80,-341,-106,83,260,171,12,4,-40,-150,-56,121,45,-146,-63,-40,3,-37,-163,-148,-50,-59,-77,88,215,221,68,-85,-66,-25,27,-58,-189,-225,-74,225,269,-106,-110,51,-79,-163,-71,-22,-11,20,41,46,80,54,-5,-19,-119,-130,-236,-208,8,111,9,-36,41,6,-63,68,63,55,150,30,-142,-106,29,-20,-188,-87,134,60,-16,-103,-80,64,180,154,93,117,99,-112,-205,-27,-204,-186,56,47,-107,-156,-125,-79,2,52,43,93,123,96,73,79,96,99,83,-7,-132,-84,127,190,97,-122,-341,-318,-112,47,98,63,-94,-305,-282,-80,179,127,-53,-4,71,58,9,3,10,-17,-14,9,-121,-288,-158,60,70,-19,39,146,96,-12,33,85,7,-41,-150,-54,-83,-309,-309,-185,-184,-264,-248,-102,-10,7,331,275,83,34,19,-40,-85,-56,-26,-70,-11,57,-19,37,97,91,25,-157,-223,-64,59,-35,-144,-207,-20,49,-59,77,196,140,28,-21,-24,-13,-4,-117,-95,-18,61,197,171,34,-30,-31,-79,-160,-191,-156,44,290,234,48,111,159,52,-6,33,-16,-129,-71,-63,-110,-1,-22,-276,-245,-119,-53,-5,-21,-133,-83,63,72,105,120,23,-67,-56,87,170,76,-19,0,-33,-149,-57,38,28,7,-110,-247,-204,-46,-2,-48,-64,-48,0,102,67,18,-8,-104,-136,-59,21,65,7,-90,-91,-160,-111,0,46,11,-79,-45,144,219,96,124,217,153,34,-136,-189,-83,-73,-48,70,47,-100,-69,-105,-80,-164,-279,-138,-7,-24,-57,-1,70,49,-58,-115,-6,-91,-59,92,146,30,-89,-45,111,174,87,62,-23,-60,-57,-10,50,28,68,107,22,-85,-87,-22,28,-67,-276,-295,-169,-45,-49,-104,-66,52,92,32,59,194,150,93,82,71,77,17,-34,13,57,90,168,-46,-38,-8,5,-31,-79,-45,20,103,175,46,-59,-9,-44,-140,-173,-36,-28,-67,34,117,14,-43,34,134,15,-127,26,207,214,114,40,51,100,97,41,36,111,149,75,84,-24,-156,-156,-43,29,0,-4,71,-95,-43,83,-2,-121,-127,-99,-85,-65,-95,-220,-229,-110,-45,-12,0,28,-6,-37,64,153,72,-13,-8,-66,-82,-49,-5,147,173,55,-9,-32,-78,-73,-40,-24,59,0,-35,-4,-33,-31,52,175,222,131,-2,-77,25,49,1,3,41,76,78,55,-29,-108,-26,49,-64,-144,-122,-80,-5,115,162,49,-34,-11,-32,23,180,130,60,78,126,152,153,152,115,22,-71,-110,-82,-59,-61,-52,-133,-89,56,97,20,-40,-18,56,132,107,9,-11,-76,-84,-61,-1,43,32,0,-14,-17,45,82,3,-18,-28,-87,-53,42,86,59,25,18,91,202,165,90,64,42,0,-33,-27,9,51,49,-33,-52,-30,-52,-11,62,113,48,-47,-54,33,130,166,174,139,53,-5,-34,-20,-66,-93,-68,-52,-31,47,89,49,74,197,189,40,4,38,34,2,-26,-77,-122,-73,66,89,23,-66,-60,-24,-5,-2,-63,-172,-119,-20,-11,-23,-41,-26,28,63,13,-49,-13,78,108,153,88,-49,-24,10,21,29,22,-28,-93,-93,-43,-94,-141,16,78,103,123,61,-50,-92,-14,61,8,-31,-9,-6,-25,-42,-11,13,-28,-58,-7,50,15,-30,24,41,-9,-62,-74,4,106,135,77,-6,-57,-55,-13,18,-52,-22,101,77,20,-14,30,127,130,19,25,68,-11,-39,-20,41,24,4,43,66,9,-49,-5,29,-6,20,-41,-27,69,62,-9,-60,-68,-27,41,19,-78,-29,-7,-17,63,105,135,116,45,-2,-6,95,214,66,-54,-4,76,76,15,-27,-15,27,45,6,-15,-4,-37,-81,-19,49,88,85,24,-38,-33,-20,-28,-3,-26,-21,74,85,32,16,34,47,65,83,34,-19,3,43,96,109,82,57,40,16,13,57,80,46,-32,4,43,0,-40,-46,-22,-7,-4,2,-23,-37,-20,-58,-66,-33,-13,-28,-5,49,53,2,-14,24,67,-11,-53,9,24,0,-18,-48,-70,-39,5,2,-5,13,-1,-29,-72,-60,-3,26,27,24,4,-1,-12,-8,57,0,-23,7,-41,-82,-51,-10,5,41,72,17,-17,-1,15,27,23,22,-27,-94,-72,3,-17,-46,-49,-18,40,21,-112,-159,-92,-59,-61,20,79,41,-38,15,22,-130,-140,-10,42,3,-22,-40,-60,13,40,-2,-11,-32,-45,-45,-29,-14,-5,11,37,39,-12,-15,12,14,11,37,43,42,58,49,-17,-64,-47,48,82,20,-8,-32,-21,-21,-49,-45,2,1,-4,-64,-88,-59,-34,-35,-13,9,-3,-16,1,6,51,83,30,38,-24,-130,-94,-32,-40,-38,2,-7,-19,-8,-82,-58,12,56,41,-2,-6,30,46,27,17,0,17,25,-18,-15,-5,8,30,31,19,30,44,15,30,25,22,15,-30,-60,-75,-54,-22,-46,-103,-99,-41,25,54,75,69,56,13,-8,-8,-32,-66,-79,-55,31,103,47,-58,-56,-28,-8,6,22,40,25,-3,33,21,34,73,64,38,11,-20,-28,5,45,48,18,-9,-15,-30,-32,-8,5,-21,-49,-21,33,19,-11,-3,-3,45,46,6,-21,-41,-36,-3,20,23,-1,-16,26,3,1,33,67,85,78,61,35,-7,0,92,44,-16,-20,-23,-15,-42,-68,-67,-53,-24,14,-20,-58,-41,-53,-35,0,-11,-32,-18,10,24,40,45,34,35,43,14,-26,-15,6,8,3,-1,-4,33,46,37,59,54,34,13,0,-5,6,33,36,-7,-41,-30,22,17,0,-14,-20,-21,-30,-34,-3,43,38,-9,17,2,0,35,73,79,47,17,14,16,20,18,-12,-4,-5,-40,-25,-9,-10,20,49,-3,-24,12,3,3,21,19,-11,-13,17,36,28,5,-26,-53,-43,11,2,-3,8,-13,-28,-12,0,-13,-27,-33,-34,-29,-11,7,14,0,-16,-14,0,0,-29,-26,7,22,-1,-15,11,16,-16,-28,-18,-31,-48,-24,-4,-8,-22,-7,-5,-7,5,47,68,38,6,17,13,-16,-24,-22,-16,-35,-41,-28,-15,-13,-6,1,-21,-47,-24,-12,-35,-20,16,24,12,12,14,-11,-43,-12,18,-3,-17,-28,-24,-15,-22,-37,-36,-12,16,15,2,-26,-40,-33,-17,10,12,9,26,32,9,12,2,-7,10,2,-2,-8,-23,-19,-1,0,-16,-30,5,31,14,5,-9,-8,-4,-4,2,13,9,1,1,-1,-11,-43,-57,-44,-38,-34,-25,-25,-27,-13,0,0,18,10,-37,-20,-4,-11,-9,13,23,2,-6,5,-19,-8,-9,-11,19,44,43,33,25,13,0,0,18,5,-9,0,13,-4,-24,-16,-2,-7,-23,-49,-35,15,29,-2,-34,-21,17,38,25,6,4,-8,-4,12,-15,-6,-3,-12,-9,-3,-2,0,6,26,11,-12,4,-20,-13,-2,2,11,20,21,15,6,2,-8,3,20,7,-14,-23,-23,-21,-19,-25,-29,-9,16,18,-10,-7,10,6,5,18,21,2,-17,-24,-31,-17,23,19,6,13,20,17,6,0,7,17,5,-12,-3,-3,-10,-7,-3,-5,-7,-7,-4,4,12,9,5,8,13,10,6,1,0,3,0,-6,0,4,11,5,-7,-13,-21,-18,1,18,18,6,-2,-7,-9,-14,-10,-4,3,0,-10,-12,-6,-4,3,0,0,0,2,5,-2,-9,-21,-27,-19,-8,0,7,17,14,-2,-3,5,9,9,10,4,-7,-13,-2,10,5,-13,-20,-5,5,7,6,4,2,1,0,0,1,8,5,6,10,1,2,18,23,6,-3,6,16,3,-18,-20,-14,-8,-2,0,2,3,-3,-13,-8,-5,-7,-2,0,-3,-5,0,4,1,-3,-10,-15,-5,3,-2,-2,0,-2,0,9,16,15,9,-2,0,11,2,0,-4,-5,-4,-9,-7,6,10,0,-14,-10,0,8,13,2,-2,2,3,-1,0,4,0,-2,4,5,6,2,0,-3,-5,-6,-7,-4,4,1,0,7,9,6,6,0,0,11,15,9,4,-4,0,-2,-8,-3,4,6,0,-4,-1,0,-2,-5,-11,-2,1,0,-3,-8,-8,0,4,0,-4,-3,6,6,1,-2,-12,-8,1,5,4,5,6,5,-5,-2,-1,-2,6,10,11,10,7,3,-2,-7,-4,3,6,0,-1,1,2,3,1,-1,0,0,-2,1,1,0,6,4,2,1,-1,-2,0,-2,-4,-1,-2,1,0,-9,-4,7,10,4,0,-3,-3,-2,0,0,2,2,1,6,7,5,3,-2,-10,1,12,1,-4,-3,0,1,0,-1,-3,-5,-4,0,-5,-10,-4,-5,-5,-4,-6,-4,0,1,-1,-2,-1,-2,0,0,0,1,1,-1,-1,1,4,5,0,-2,-1,0,1,1,0,-2,-1,0,0,-1,1,3,6,4,2,2,1,1,0,0,3,6,4,3,3,0,-3,-3,0,3,3,1,0,-1,-1,3,0,-1,1,0,0,0,0,2,1,-1,-1,0,1,2,1,1,3,1,0,3,4,2,1,2,3,0,0,0,1,1,0,0,0,0,0,-1,-3,-5,-3,-1,0,-1,-2,0,2,2,2,1,0,-1,-1,-2,-1,-1,0,0,0,-1,-3,-5,-4,0,1,0,-3,0,1,1,0,0,0,1,2,2,1,0,-2,-1,0,0,-1,-1,0,0,0,0,-1,-2,-1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,-1,0,0,1,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,1,0,0,0,1,0,-1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
       };
};
#endif