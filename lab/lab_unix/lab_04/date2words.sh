# Checking for more than one argument
if [ $# -ge 2 ] ; then
    printf "date2words: usage ./date2words [date]\n"
    exit 1
fi

# Getting date in three parts
year=$(date +%Y -d "$1") || exit $?
month=$(date +%m -d "$1") || exit $?
day=$(date +%_d -d "$1") || exit $?

# Checking what we have so far
# printf "%s-%s-%s\n" "$year" "$month" "$day"

# Making day_string
day_p1=${day:0:1}
day_p2=${day:1:1}

day_string=""
if [ "$day_p1" != "1" ] && [ "$day_p2" != "0" ]; then
    case $day_p1 in
        "0")
            day_string_p1=""
            ;;
        "2")
            day_string_p1="двадцать "
            ;;

        "3")
            day_string_p1="тридцать "
            ;;
    esac

    case $day_p2 in
        "1")
            day_string_p2="первое"
            ;;
        "2")
            day_string_p2="второе"
            ;;
        "3")
            day_string_p2="третье"
            ;;
        "4")
            day_string_p2="четвёртое"
            ;;
        "5")
            day_string_p2="пятое"
            ;;
        "6")
            day_string_p2="шестое"
            ;;
        "7")
            day_string_p2="седьмое"
            ;;
        "8")
            day_string_p2="восьмое"
            ;;
        "9")
            day_string_p2="девятое"
            ;;
    esac
    day_string="$day_string_p1$day_string_p2"
else
    case $day in
        "10")
            day_string="десятое"
            ;;
        "11")
            day_string="одиннадцатое"
            ;;
        "12")
            day_string="двенадцатое"
            ;;
        "13")
            day_string="тринадцатое"
            ;;
        "14")
            day_string="четырнадцатое"
            ;;
        "15")
            day_string="пятнадцатое"
            ;;
        "16")
            day_string="шестнадцатое"
            ;;
        "17")
            day_string="семнадцатое"
            ;;
        "18")
            day_string="восемнадцатое"
            ;;
        "19")
            day_string="девятнадцатое"
            ;;
        "20")
            day_string="двадцатое"
            ;;
        "30")
            day_string="тридцатое"
            ;;
    esac
fi

# Making month_string
case $month in
    "01")
        month_string="января"
        ;;
    "02")
        month_string="февраля"
        ;;
    "03")
        month_string="марта"
        ;;
    "04")
        month_string="апреля"
        ;;
    "05")
        month_string="мая"
        ;;
    "06")
        month_string="июня"
        ;;
    "07")
        month_string="июля"
        ;;
    "08")
        month_string="августа"
        ;;
    "09")
        month_string="сентября"
        ;;
    "10")
        month_string="октября"
        ;;
    "11")
        month_string="ноября"
        ;;
    "12")
        month_string="декабря"
        ;;
esac

# Substituting results
printf "%s %s %s-го года\n" "$day_string" "$month_string" "$year"
