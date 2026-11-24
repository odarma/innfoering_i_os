# du må lage filen når du kjører koden

fil=$1

if [ ! -e "$fil" ]; then
    echo "Feil: Filen finnes ikke!"
    exit 1
fi

gammel_size=$(stat -c "%s" "$fil")

while true; do
    sleep 1

    ny_size=$(stat -c "%s" "$fil")

    if [ "$ny_size" -ne "$gammel_size" ]; then
        echo "Filen er endret!"
        rm "$fil"
	exit 0
    fi
done
