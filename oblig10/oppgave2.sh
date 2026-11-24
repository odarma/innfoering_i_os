innhold_fra="$1"
innhold_til="$2"

mkdir "$innhold_fra"
mkdir "$innhold_til"

touch "$innhold_fra"/sang1.mp3
touch "$innhold_fra"/sang2.mp3
touch "$innhold_fra"/notat.mp3

antall=0

for i in "$innhold_fra"/*.mp3;
do
	mv "$i" "$innhold_til"
	((antall++))
done

echo "flyttet $antall mp3-filer fra $innhold_fra til $innhold_til"

rm -r "$innhold_fra"
rm -r "$innhold_til"
