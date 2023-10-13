#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char EgriCsillagok[][16] = { "ablak", "ablakocska", "ablakos", "abonyban", "adasson", "add", "adhatja", "adjon", "adni", "adok", "adtak", "aggasztotta", "aggodalom", "agyagba", "agyonvert", "ahmednek", "ahova", "ajkakkal", "akadt", "akaratomat", "akarja", "akarod", "akarta", "akartok", "akasszon", "akik", "akinek", "akkordjai", "akkorra", "alacsony", "alakban", "alakra", "alattuk", "ali", "alighogy", "alkalommal", "alkonyatra", "alkudtam", "alma", "almagyaron", "alszom", "altisztek", "aludna", "aludtam", "amaz", "amellett", "amelyekben", "amelyen", "amelyiken", "amellyel", "amennyire", "amije", "amilyenek", "amint", "amulett", "angyal", "anna", "anyai", "annyi", "annyit", "apjuk", "arabs", "aranyak", "aranygombjait", "aranyos", "aranyszarv", "araszos", "arccal", "arcomat", "arcra", "arra", "aszongya", "asszonyi", "asszonyokhoz", "asszonyt", "asztalra", "atyafival", "augusztusi", "avult", "azazhogy", "azokat", "azoknak", "azonnal", "babadzsizi", "bagolyarcot", "bajodban", "bajszos", "bajuszom", "bakancs", "bakocsaira", "balaton", "ballagott", "balta", "bariton", "barom", "batyu", "becsapott", "bedobtak", "beesett", "befordulok", "befutott", "behajtja", "behatoltak", "behozatta", "behunyjuk", "bejuthassanak", "bekapcsolja", "belecsapott", "beledobolni", "beleereszkedtek", "beleharapott", "belekapott", "belemarkolt", "beleolvasta", "belerikoltott", "beletette", "bemegy", "bement", "bemutatva", "bennetek", "benyitott", "beosont", "berakva", "besiet", "beszakadnak", "betakarta", "betegek", "beteheti", "betoppant", "beugrok", "bevezetheted", "bevont", "biccentett", "bilincsben", "bilincsem", "birka", "birokkal", "birtokait", "bivaly", "biz", "bizalommal", "bizonyosabb", "biztat", "biztosan", "bodzafa", "bokor", "bokros", "boldogan", "boldogulunk", "bolondoztak", "boltozata", "boltozott", "boncsokok", "bontja", "bontsatok", "borlevest", "borospince", "borulj", "borultan", "bosnya", "bot", "botozta", "budai", "bukdossanak", "bukjon", "bum", "burrogva", "cecey", "cimbalom", "cipelne", "ciprusok", "combvasat", "csaholnak", "csaknem", "csalni", "csapata", "csapatokat", "csapatot", "csapkodja", "csapnak", "csapta", "csata", "csatlakoztok", "csattant", "csavar", "csavarva", "cselekedd", "cselekedjek", "cselekszek", "csemcsegetve", "csendet", "cseppekben", "cserepesen", "csiholj", "csillaghoz", "csillagokon", "csillogtak", "csitt", "csoda", "csontja", "csontot", "csoportnak", "csoportosuljon", "csorba", "csukjuk", "csupaszon", "csurom", "dagadt", "dali", "daloljanak", "dalolt", "dalt", "danoljak", "danoltak", "darabokat", "darabra", "debrecen", "debrecent", "dejszen", "delire", "derekamon", "dermedt", "derviseket", "dervisre", "diadal", "dicsekedni", "dinnye", "dob", "dobognak", "dobon", "dobost", "dobva", "dolgodban", "dolgozhassanak", "dolgozni", "dolgoztatnunk", "dolguk", "dombokat", "domborodtak", "donga", "dugja", "duhogta", "dunyha", "durrogva", "duzzogva", "ebben", "ebnek", "edd", "egek", "egerig", "egri", "egybefolyt", "egyebet", "egyenes", "egyenletesen", "egyetlenegy", "egyikben", "egyiptomiak", "egymagam", "egyszer", "egyvalamit", "ej", "ejtettek", "eladja", "elakadt", "elbillen", "elbumbumozta", "elcsillapodjon", "eledel", "elegyedik", "elejti", "elesik", "elevenen", "elfelej", "elfelejtetted", "elfogadja", "elfogadott", "elfogna", "elfogyott", "elfulladt", "elfutott", "elgondolkodva", "elhagyni", "elhajtottad", "elhallgat", "elhanyatlott", "elhervadtak", "elhozni", "eligazodom", "elindult", "eljutnak", "elkapom", "elkergeti", "elkomolyodott", "ellene", "ellenkezik", "ellobbant", "elmaradt", "elmehessenek", "elmenetelemet", "elment", "elmondani", "elmondtad", "elmosolyodtak", "elnyelte", "eloldotta", "elolvastatom", "elpirosodva", "elpukkannak", "elragadja", "elriasztgatni", "elrogyik", "elsoroltak", "elszontyolodva", "eltegye", "eltorzul", "elveszed", "elveszte", "elvette", "elvigyorodik", "elvillant", "elvitted", "elvonulhasson", "embere", "emberek", "emberemmel", "emberkarnyi", "emberrel", "emeleten", "emelgette", "emelkedett", "emelni", "emez", "emlegette", "engedelmesek", "engedetlen", "engedje", "engedtek", "enni", "ennyi", "ered", "eredve", "eresz", "ereszkedjen", "eresztem", "eresztettek", "eretnek", "esembe", "esni", "estem", "esze", "eszeltetek", "eszemmel", "eszik", "esztendeje", "ettek", "evezz", "ezekben", "ezen", "ezernyi", "ezrek", "fa", "fagyosan", "fakadt", "fakasztotta", "falai", "falakkal", "falatozott", "falba", "falkaraj", "falon", "falubeli", "falujukban", "falut", "fanyereg", "faragva", "farkasszemet", "fecsegtek", "fedeztem", "fegyvereddel", "fegyverek", "fegyveres", "fegyverkezve", "fej", "fejeden", "fejemen", "fejetek", "fejire", "fejsze", "fekszem", "fektette", "felakasztatom", "felbillentik", "felcsatolta", "feledje", "felejtesz", "felelet", "felelhetett", "felelne", "felelte", "felfalta", "felfordult", "felfutott", "felhatolt", "feljebb", "felkapcsolt", "felkel", "fellobbanva", "felnyitja", "felpattant", "felragasszam", "felrobbantottuk", "feltegyelek", "felugrott", "felzavartak", "fenevadak", "fent", "ferencet", "festeni", "festik", "fiadat", "fiaim", "fiam", "fiatalabb", "fiataljainkat", "figyel", "figyelmet", "finom", "fizesd", "fog", "fogadj", "fogadom", "fogai", "fogatokat", "fogja", "foglalja", "foglalni", "foglyot", "fogoly", "fogom", "fogtak", "fogva", "fojtott", "fokosok", "foltot", "folyna", "folytassam", "folytatniuk", "fonott", "fontot", "forduljak", "fordulni", "fordultak", "forgatja", "forgok", "forintot", "forogsz", "fosztogatod", "friss", "furakodhattak", "fussatok", "futkos", "futnak", "futottak", "futva", "gabona", "gasparics", "gazember", "gerenda", "gergelyedhez", "gergelyt", "gomb", "gombolta", "gondod", "gondolatai", "gondolatokra", "gondolhatja", "gondolkodj", "gondolkozik", "gondolnak", "gondolom", "gondoltuk", "gondoskodnia", "gondunk", "gubancos", "gurgula", "gyakorta", "gyaloghadra", "gyalogosok", "gyaluban", "gyaurnak", "gyepen", "gyerek", "gyerekeknek", "gyerekkel", "gyermeke", "gyermekeiket", "gyermekeket", "gyermeket", "gyermekkor", "gyermekruha", "gyilkot", "gyomor", "gyorsabban", "ha", "habozva", "hadak", "hadba", "hadirendben", "hadnagyok", "hadnagyunkat", "hadseregbe", "hagyd", "hagyjuk", "hagynotok", "hagytad", "haja", "hajfonat", "hajlik", "hajnalban", "hajnalra", "hajolt", "hajtja", "halad", "halas", "halkan", "hallatszottak", "hallgat", "hallgatnak", "hallgatott", "hallgatva", "hallod", "hallottam", "halmokon", "halom", "halottaikat", "halottaknak", "halotti", "haltatok", "hamarosan", "hang", "hangokat", "hangosan", "hangzik", "hanyatlott", "haragjuk", "haragszik", "harangok", "harapj", "harasztban", "harci", "harcolhatunk", "harcolt", "harcoltunk", "harcot", "harmadikat", "harmanli", "harminc", "harminchat", "harsogja", "harsogva", "hasba", "haszna", "hatalmuk", "hatol", "hatvan", "havas", "hazaindultak", "hazaszeretet", "hazudnak", "hebegi", "hegyeken", "hegyesre", "hegyin", "hegyre", "helyeken", "helyett", "helyre", "hercegek", "hetedik", "hetetlen", "hetvennyolc", "hevert", "hiba", "hidegen", "hinni", "hirdetett", "hiszem", "hit", "hitetlenek", "hittem", "hogyan", "hogysem", "holdatlan", "holnap", "holtak", "holtan", "holtra", "homlokkal", "homokon", "hoppra", "hordanom", "hordatok", "hordott", "hordozok", "hordta", "horgozza", "hosszan", "hoz", "hozatott", "hozhattak", "hoznod", "hozott", "hozz", "hull", "hulljon", "hullt", "hunyadinak", "huppognak", "huszadik", "icce", "idegen", "ideges", "idei", "iderendelt", "igazabban", "igazi", "igyekezett", "ihasson", "ijedt", "illant", "illedelmes", "illeti", "ily", "ilyent", "inakodott", "indulat", "indulnom", "indulunk", "ingatta", "ingesen", "innen", "inogtak", "intelek", "intsen", "iparosok", "irgalmazzanak", "is", "ismerek", "ismerik", "ismersz", "isten", "istenemre", "istent", "iszen", "iszol", "ital", "itatni", "ittak", "izabella", "izente", "izmail", "izomtalan", "jaja", "jajgatva", "jancsira", "java", "jegesen", "jegyzett", "jelenet", "jelenni", "jelentem", "jelentettem", "jelentsd", "jeleztek", "jobb", "jogunk", "juliska", "jutalmad", "jutalomra", "jutni", "jutott", "juttatott", "kacagtak", "kaktuszok", "kalauzolta", "kancsal", "kanyarodtak", "kaparta", "kapaszkodva", "kapdosta", "kapjanak", "kapkodjatok", "kapni", "kapott", "kapta", "kapu", "kapuhoz", "kapukat", "kapura", "kar", "kardja", "kardod", "kardom", "kardot", "karjai", "karjukon", "karokkal", "karpereceket", "kasokat", "kassaiakat", "katekizmus", "katonaruha", "kavicsos", "kedve", "kedvesek", "kedvetek", "kegyelme", "kegyelmet", "kegyes", "kelet", "keletkezett", "keljen", "kellenek", "kelni", "kemence", "kendnek", "kenyere", "kerekebbre", "kerekek", "keres", "keresetem", "keresitek", "kereste", "kereszt", "keresztes", "kerget", "kertek", "kesely", "keskeny", "ketten", "keverek", "kevesebb", "kezdeni", "kezdik", "kezdve", "kezedet", "kezemet", "ki", "kibontotta", "kicsavarni", "kicsiny", "kiejti", "kiesett", "kificamodott", "kifutott", "kihagytam", "kihallatszik", "kihozott", "kiizentek", "kikelten", "kiknek", "kilincs", "kimagaslott", "kimehetsz", "kiment", "kincsedet", "kincseket", "kinizsivel", "kiolvasta", "kipirosodott", "kirakta", "kirontott", "kisasszonynak", "kisebbiket", "kisgyereket", "kisiet", "kismacska", "kiszabadult", "kiszorult", "kitekerte", "kiterjesztve", "kiugrik", "kiveszik", "kivette", "kivillantja", "kivonva", "koccintgatott", "kocsi", "kocsijuk", "kocsimat", "kocsisnak", "kocsit", "koldult", "kolomposok", "komolyan", "komorulnak", "konyha", "kopasz", "koponya", "kor", "korhol", "kormosan", "korona", "kosarat", "krucifiksz", "kulacs", "kupa", "kurddal", "kurjantott", "kuruzsolni", "kutyorodott", "lajtba", "lakatolt", "lakattal", "laknak", "lakodalomba", "laktak", "lantos", "lapos", "lappangtak", "lassan", "lator", "lebeg", "lebujdosol", "lecsatolja", "ledobta", "leeresztett", "leette", "lefogta", "legeljenek", "legfeljebb", "leghosszabb", "legkegyelmesebb", "legmagasztosabb", "legravaszabbul", "legszebbik", "legurult", "legyetek", "lehajlik", "lehajtva", "lehelte", "lehet", "lehetne", "leheveredtek", "lehullt", "leiramlott", "lekanyarodnak", "lekapott", "lekuporodva", "lelkek", "lelkemre", "lelki", "lemegyek", "leng", "lengetett", "lengyel", "lennie", "leoldottan", "lepillant", "lerontott", "lesnek", "leszakad", "lesznek", "letartotta", "leteszed", "letrappolt", "leugorva", "levele", "levelet", "leveleztetek", "leveregette", "leverte", "levest", "leveti", "levillant", "liheg", "liliomnak", "lobbanik", "lobognak", "lobogtatta", "locsog", "locsolniuk", "lombokon", "lomok", "lopnak", "losonczy", "lovag", "lovagolt", "lovaimat", "lovakat", "lovakra", "lovasa", "lovasoknak", "lovasunk", "lovukat", "luca", "lyukas", "lyukhoz", "macskaszemekben", "madzagon", "magadfajta", "magamon", "magasan", "magasra", "magatoknak", "magukat", "maguknak", "magvakra", "magyarnak", "magyaros", "maholnap", "majdan", "malmot", "malomba", "marad", "maradjak", "maradnia", "maradt", "maradtnak", "margitnak", "markodba", "markolata", "markomban", "marokkal", "martonfalvait", "matyival", "mecseteket", "medvehangon", "megadtad", "megbetegedtem", "megborzongott", "megcsapta", "megdegles", "megegyeztek", "megengedi", "megeszik", "megfejtsem", "megfelelek", "megfog", "megfogott", "megfojtott", "megfordult", "meggondoljuk", "meghajolni", "meghajszolta", "meghallgatod", "meghalmozta", "meghalsz", "meghanyatlott", "meghatja", "meghordta", "megindultak", "megint", "megismeri", "megissza", "megjegyzett", "megjelentse", "megkeresnem", "megkezdik", "meglegyintek", "meglepte", "megloptak", "megmenteni", "megmondhatom", "megmondottad", "megmosdatta", "megmutatom", "megneszelte", "megnyargalta", "megnyugszik", "megolvasta", "megpihenjen", "megragad", "megrakodottan", "megreszketett", "megrezzenve", "megritkul", "megsereglik", "megsokallta", "megszakadt", "megszeppenve", "megtapogatta", "megtartsa", "megtekinteni", "megtenni", "megtetszik", "megtudd", "megtudod", "megvakarta", "megvannak", "megveszed", "megvillanik", "megzavarodik", "megzavarodva", "megyek", "mehetnek", "mekcseyhez", "melegedett", "melegszenek", "mellemben", "mellest", "mely", "menet", "menetet", "menjen", "menni", "menten", "mentsenek", "menyecske", "mennyezetek", "mennyivel", "meredeznek", "mereszti", "merjetek", "merte", "mesebeli", "mesterkedni", "metszened", "meztette", "miben", "mihelyst", "mikor", "mind", "mindazok", "mindenben", "mindenesnek", "mindenikkel", "mindenki", "mindenkivel", "mindennapos", "mindezek", "mindnek", "minket", "mintsem", "miska", "mivel", "mohamed", "mondani", "mondatonkint", "mondhat", "mondja", "mondod", "mondotta", "mondva", "morajlott", "mormogja", "mormolt", "morogva", "mosakodnak", "mosdott", "mosolyog", "most", "mostohaanyja", "mozdulatait", "mozdulatot", "mozduljon", "mozgatja", "mozog", "mozsarat", "mulatozik", "mulattattunk", "mutasd", "mutatkozik", "mutatok", "mutattak", "muzsika", "nagyban", "nagykapun", "nagyokat", "nagyurak", "napig", "naplemente", "napod", "napos", "napra", "negyedik", "negyvenkilenc", "neked", "nekiesik", "nekik", "nekiugrik", "nemegyszer", "nemesurak", "nemzet", "nemzeti", "nesztek", "nevedet", "nevelkedett", "nevet", "nevettek", "nevezi", "ni", "no", "nyakadra", "nyakat", "nyakukon", "nyargal", "nyavalya", "nyelv", "nyer", "nyerge", "nyerges", "nyihogva", "nyilallik", "nyirok", "nyitni", "nyitva", "nyolcvan", "nyomakodnak", "nyomorodva", "nyomtak", "nyomunkba", "nyugasztva", "nyugodott", "nyugtalanabban", "nyulak", "odaadja", "odaadtam", "odacipelte", "odafordul", "odakap", "odalent", "odaomlott", "odarohan", "odasorakozott", "odatolongott", "odaveszett", "odavezette", "oka", "okoskodj", "oktatni", "olajat", "olaszok", "old", "oldalon", "oldallyukon", "oldozd", "oltalmazza", "olvasatlanul", "olvasom", "olvastam", "olyanforma", "olyat", "omolt", "orgonabokrokkal", "oromra", "orrodat", "orvosai", "ostorral", "ostrommal", "ostromra", "oszlopai", "oszlopon", "oszoltan", "osztani", "osztotta", "otromba", "otthagyod", "pad", "padra", "pajzsok", "pajzsul", "pallost", "panni", "papirosaidat", "papirosra", "paplan", "papokkal", "paprika", "papunk", "paradicsombeli", "parancsolja", "parancsolok", "paraszt", "parasztgyereket", "parasztok", "paraszttal", "partja", "patak", "patakot", "pattintunk", "pazarolta", "pedig", "pelyhekben", "pengette", "percek", "percnyi", "peregve", "pergett", "pestet", "petrovich", "piaci", "piasztert", "pihenhettek", "pihennem", "pikkelyes", "pillanatot", "pillantott", "pince", "pirosan", "pirosra", "pista", "pitypang", "pofont", "pokolba", "pokolszerrel", "pontokra", "porba", "porosan", "port", "potrohos", "puhafa", "pulykacomb", "puskaporhoz", "puskaporral", "pusztultok", "puttonyos", "rabjai", "rablott", "raboknak", "rabolva", "rabra", "ragadja", "ragaszd", "ragyogott", "rajtad", "rajza", "rajzolt", "rajzott", "rakatott", "rakjunk", "rakodottan", "rakta", "ravasz", "rebegte", "recsegve", "reggeli", "rejtekfaluban", "rekedt", "remegett", "remeteudvaron", "rendelem", "rendelkezett", "rendelkezzen", "rendelve", "rendezkedni", "rengeteg", "restellte", "reszketteti", "rettenjen", "rezet", "riadalom", "rikkant", "rikoltnak", "rikoltva", "ritkult", "robognak", "rogyadozik", "rohannak", "rohanva", "rokonaihoz", "romhalmot", "ronda", "rongyok", "rongyosabb", "rontanak", "rontotta", "ropognak", "roppant", "rosszabb", "rotyogott", "rudakat", "rudat", "sajtot", "sakkoztak", "sarka", "sarkon", "sarokban", "sastollas", "sebek", "sebhely", "sehol", "sejteni", "selyem", "selyemmel", "semmi", "senki", "sercegett", "serege", "sereggel", "siessek", "sietnek", "siket", "sikoltozva", "simogatni", "sincsen", "sisak", "sisakkal", "sisakos", "sistergett", "sodorta", "sokadozik", "sokkal", "somfagallyal", "sophia", "sora", "sorban", "sorra", "sort", "stambulba", "sugaraiban", "suhant", "susog", "sustorogva", "szabadban", "szabadultam", "szabtam", "szaggatta", "szagot", "szakadozni", "szakasztott", "szaladt", "szalkayt", "szapolyait", "szaporodtak", "szarvas", "szavai", "szavaknak", "szavamnak", "szebbnek", "szedetett", "szednek", "szedtek", "szegezte", "szeglettorony", "szekerek", "szekerekre", "szelemenfa", "szeletet", "szem", "szemed", "szemeket", "szemes", "szendergett", "szentelem", "szepegett", "szerb", "szerecsent", "szeren", "szeret", "szeretetben", "szeretitek", "szerette", "szereznek", "szerint", "szerzett", "sziget", "szikra", "szirt", "szokatlan", "szokta", "szolakok", "szolnokot", "szomjazom", "szopta", "szorul", "szurkot", "szusszant", "tagokat", "takarodj", "takarta", "talpig", "tanakodtak", "tanult", "tapasztalt", "tapint", "tapogassa", "tar", "tarisznya", "tart", "tartania", "tartja", "tartok", "tartottak", "tartozunk", "tartsd", "tavasz", "te", "tegnapi", "tegyetek", "tehet", "tehetne", "tekercs", "tekintet", "tekintetes", "tekintettel", "tele", "telepedjek", "telken", "temessenek", "temetnek", "templomba", "templomodban", "tengerbe", "tengerparton", "tenyere", "tereket", "teremhez", "teremtette", "terjed", "terjegetve", "termeibe", "termet", "tessen", "teste", "testesebb", "teszek", "tesztek", "tetszettek", "tettek", "tietek", "tilalmas", "tiporja", "tiszta", "tiszteknek", "tiszteletes", "tisztes", "tisztje", "tisztjeire", "tisztogatta", "titka", "titkos", "tizedesnek", "tizenegyen", "tizennyolcadik", "tolakodott", "toll", "tolong", "tolultak", "tomporomat", "topcsiknak", "toppantott", "tornyai", "tornyon", "torony", "toronynak", "trombita", "tudd", "tudjuk", "tudnom", "tudott", "tudtok", "tulajdonosa", "tutulnak", "udvari", "udvarra", "ugorjatok", "ugratni", "ugrottam", "ugyanannyi", "ugyanekkor", "ugyanott", "ujjain", "ujjongtak", "ura", "uraink", "uraknak", "uramnak", "urunkat", "utam", "utat", "utca", "vacogott", "vadaskertben", "vagyis", "vagytok", "vajon", "vakarintott", "vakolat", "vakolnak", "vakulva", "valahol", "valakivel", "valamelyiknek", "valamennyinek", "valamikor", "valamit", "vallunk", "varr", "varrniuk", "varrtak", "vasakarata", "vasba", "vaskapcsot", "vasport", "vastagon", "vedd", "veje", "veletek", "verebek", "verekedik", "verekszem", "veresborral", "verette", "vermeket", "verseny", "vert", "verve", "vesz", "veszedelmeknek", "veszekedjenek", "vesszenek", "vesztve", "vetettek", "vetkezetten", "vettek", "vezesd", "vezetett", "vezette", "viadal", "viaszolva", "vidd", "vigye", "vigyorog", "viharosan", "villant", "villognak", "vinni", "virradatkor", "virrasztaniuk", "viselje", "viselte", "viszek", "viszketett", "visszaadva", "visszafojtott", "visszafordultok", "visszahozta", "visszanevet", "visszarohant", "visszatekint", "visszatorpannak", "visszavezette", "vitetett", "vizes", "volt", "voltunk", "vonalas", "vonatott", "vonszolva", "vontatnak", "vonulni", "zabozott", "zavarja", "zavaros", "zene", "zivatarba", "zoltaynak", "zuhannak", "zuhognak", "zsebekben", "zsibajgott", "zsilip", "zsineg", "zsoldost", "" };

void f1();
void f2();

typedef enum Hangrend { magas, mely, vegyes } Hangrend;
Hangrend hangrend(char *szo);
void f3();

bool sorban(char *szo);
void f4();

void f5();

int main() {
    f1();
    f2();
    f3();
    f4();
    f5();
}

void f1() {
    printf("1. Keresett szó: ");
    char target[16];
    scanf("%s", target);
    for (int i = 0; EgriCsillagok[i][0] != 0; i++) {
        char *source = EgriCsillagok[i];
        if (strstr(source, target) != NULL)
            printf("%s ", source);
    }
    printf("\n\n");
}

void f2() {
    printf("2. Vizsgált szó: ");
    char target[16];
    scanf("%s", target);
    char mgh = 0;
    for (int i = 0; target[i] != 0; i++) {
        char c = target[i];
        c = tolower(c);
        if (strchr("aeiou", c) != NULL) {
            if (mgh == 0 || mgh == c)
                mgh = c;
            else {
                printf("különféle magánhangzókat tartalmaz\n");
                return;
            }
        }
    }

    if (mgh != 0)
        printf("csak egyforma magánhangzókat tartalmaz\n");
    else
        printf("nem tartalmaz magánhangzót\n");
}

Hangrend hangrend(char *szo) {
    int vanMagas = 0, vanMely = 0;
    for (int i = 0; szo[i] != 0; i++) {
        char c = szo[i];
        if (strchr("ei", c) != NULL)
            vanMagas = 1;
        else if (strchr("aou", c) != NULL)
            vanMely = 1;
    }

    return vanMagas && vanMely ? vegyes
                               : vanMagas ? magas
                                          : vanMely ? mely
                                                    : -1;
}

void f3() {
    printf("\n3. feladat\n");

    int magasDb = 0, melyDb = 0, vegyesDb = 0, egyebDb = 0;

    for (int i = 0; EgriCsillagok[i][0] != 0; i++) {
        char *szo = EgriCsillagok[i];
        Hangrend hr = hangrend(szo);
        switch (hr) {
            case magas: magasDb++; break;
            case mely: melyDb++; break;
            case vegyes: vegyesDb++; break;
            default: egyebDb++; break;
        }
    }

    double sum = magasDb + melyDb + vegyesDb + egyebDb;
    printf("magas: %d (%.2f%%)\n", magasDb, magasDb * 100 / sum);
    printf("mély: %d (%.2f%%)\n", melyDb, melyDb * 100 / sum);
    printf("vegyes: %d (%.2f%%)\n", vegyesDb, vegyesDb * 100 / sum);
    printf("egyéb: %d (%.2f%%)\n\n", egyebDb, egyebDb * 100 / sum);
}

bool sorban(char *szo) {
    for (int i = 1; szo[i] != 0; i++)
        if (szo[i - 1] > szo[i])
            return false;
    return true;
}

void f4() {
    printf("4. feladat\n");

    for (int i = 0; EgriCsillagok[i][0] != 0; i++) {
        char *szo = EgriCsillagok[i];
        if (sorban(szo))
            printf("%s ", szo);
    }
    printf("\n\n");
}

char* middle(char* first, char* last) {
    return first + (last - first) / 16 / 2 * 16;
}
void f5() {
    printf("5. feladat\n");

    int len = 0;
    while (EgriCsillagok[len][0]) len++;
    
    for (int i = 0; EgriCsillagok[i][0] != 0; i++) {
        char *szo = EgriCsillagok[i];
        char kep[14];
        int j;
        for (j = 0; szo[j + 2] != 0; j++)
            kep[j] = szo[j + 1];
        kep[j] = 0;

        char* first = EgriCsillagok[0];
        char* last = EgriCsillagok[0] + (len - 1) * 16;

        while (first <= last) {
            char* mid = middle(first, last);
            int cmp = strcmp(kep, mid);
            if (cmp == 0) {
                printf("%s -> %s\n", szo, kep);
                break;
            } else if (cmp < 0)
                last = mid - 16;
            else
                first = mid + 16;
        }
    }
}
