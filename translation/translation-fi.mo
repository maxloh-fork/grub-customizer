��    x      �  �   �      (
  	   )
  8   3
  !   l
     �
     �
     �
  E   �
       "     
   3  	   >     H  1  T     �  %   �  &   �     �  /      '   0  -   X     �     �     �  %   �  M   �  "   -  q   P     �     �     �  &   �  $         E     T     h     x     �     �     �  '   �  &   �          )     1  $   G     l  .   �  �   �  *   k  ^   �  �   �  8   �     �  G   �         -  .   0  �   _  	   �  	   �          
                    3     H     ]     j     y          �  
   �     �     �     �     �     �     �       	          
   -     8     R  
   X     c  	   �     �     �  
   �  
   �  
   �     �     �  	   �     �            !     )     5     :  	   B     L     Z     s     w     �  *   �     �  	   �     �     �     �     �       
        $     *  �  1     �  4   �  #     !   ?     a     �  Q   �     �     �          (     5  <  C     �  "   �  "   �     �  5   �  '   '  #   O      s     �  -   �  +   �  P   �  "   O  r   r     �     �  /     =   <  >   z     �     �  !   �        "   )      L       X      y      �      �      �      �   -   �   8   !  ,   P!  �   }!  &   P"  l   w"  �   �"  F   �#     �#  U   �#  )   +$  `  U$  3   �%  �   �%     �&     �&     �&  	   �&  	   �&     �&     �&     �&     �&     '     $'     9'      B'  ;   c'     �'  
   �'     �'     �'     �'  *   �'     �'     (     (     "(     9(     H(     c(     k(      w(     �(     �(     �(     �(     �(     �(     �(     �(     )     )  #   5)     Y)     a)     p)  	   u)     )     �)      �)     �)     �)     �)  >   �)  	   #*     -*     =*     K*     R*     i*     �*  	   �*  	   �*  	   �*        /   1                -              +   c       k       x   A   j          T   "          !   &   `   l   *   C   <       ,       (   m      w   @              i       b   q          
   [       a   ;       o      e   4   .           N           _         F   v   Y   #   s   0   G   I          L   :   6       Q          O   h       ]      K   '   V      \   5   r           E   S       %       7   X   g   H   $       9          Z       D           3   p                 M   U      ^   >   R   n                   2       W   )       P   f   u                          d   	   t          B   =   ?   8       J        (custom) %1 couldn't be executed successfully. error message:
 %2 %1 not found. Is grub2 installed? (new Entries of %1) (new Entries) (script code) AND: your modifications are still unsaved, update will save them too! A_ppearance Add a script to your configuration Add script BURG Mode BURG found! Before you can edit your grub configuration we have to
mount the required partitions.

This assistant will help you doing this.


Please ensure the target system is based on the same cpu architecture
as the actually running one.
If not, you will get an error message when trying to load the configuration. Configuration has been saved Couldn't mount the selected partition Couldn't umount the selected partition Default title:  Do you want to configure BURG instead of grub2? Do you want to save your modifications? Do you want to select another root partition? Edit grub preferences Entry Entry %1 (by position) Error while installing the bootloader Grub Customizer is a graphical interface to configure the grub2/burg settings Grub Customizer: Partition chooser Install the bootloader to MBR and put some
files to the bootloaders data directory
(if they don't already exist). Install to MBR Mount failed! Mount selected Filesystem Move down the selected entry or script Move up the selected entry or script Name the Entry No Bootloader found No script found Partition Chooser Please type a device string! Preview: Proxy binary not found! Remove a script from your configuration Save configuration and generate a new  Script to insert: Seconds Select _partition … Select and mount your root partition Select required submountpoints The bootloader has been installed successfully The generated configuration didn't equal to the saved configuration on startup. So what you see now may not be what you see when you restart your pc. To fix this, click update! The saved configuration is not up to date! These are the mountpoints of your fstab file.
Please select every grub/boot related partition. This option doesn't work when the "os-prober" script finds other operating systems. Disable "%1" if you don't need to boot other operating systems. This seems not to be a root file system (no fstab found) Timeout To get the colors above working,
you have to select a background image! Unmount mounted Filesystem You selected the option for choosing another partition.
Please note: The os-prober may not find your actually running system.
So run Grub Customizer on the target system
again and save the configuration (or run update-grub/update-burg)
to get the entry back! You started Grub Customizer using the live CD. You will see all entries (uncustomized) when you run grub. This error accurs (in most cases), when you didn't install grub gustomizer currectly. _Advanced _Device:  _Edit _File _General _Help _Install to MBR … _Quit without saving _Quit without update _Save & Quit _Update & Quit _View _use another partition:  add this entry to a new submenu background background image black blue brown cannot move this entry custom resolution:  cyan dark-gray default entry font color generate recovery entries green highlight: installing the bootloader… is active kernel parameters label light-blue light-cyan light-gray light-green light-magenta light-red loading configuration… look for other operating systems magenta menu colors name normal: partition pre_defined:  previously _booted entry red reload configuration remove background remove this entry from the current submenu settings show menu transparent type umount failed! updating configuration value visibility white yellow Project-Id-Version: grub-customizer
Report-Msgid-Bugs-To: FULL NAME <EMAIL@ADDRESS>
POT-Creation-Date: 2011-12-23 17:05+0100
PO-Revision-Date: 2011-12-28 21:05+0000
Last-Translator: Timo Seppola <Unknown>
Language-Team: Finnish <fin@ x x x x.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Launchpad-Export-Date: 2012-01-31 23:00+0000
X-Generator: Launchpad (build 14734)
  (yksilöinti) %1 ei voitu suorittaa onnistuneesti. Virheviesti:
%2 %1 ei löydy. Onko grub2 asennettu? (Uudet käynnistysvaihtoehdot %1) (Uudet käynnistysvaihtoehdot) (komentosarja koodi) JA: Muokkauksesi ovat vielä tallentamatta,nyt päivitys tallentaa nekin samalla! _Ulkonäkö Lisää komentosarja asetuksiin Lisää komentosarja BURG tilassa BURG löytyi! Ennenkuin voit editoida grub asetuksia meidän täytyy liittää
tarvittavat osiot.

Tämä avustaja auttaa tekemään liitokset.


Ole hyvä ja varmista, että kohdejärjestelmä perustuu samaan CPU-arkkitehtuuriin
kuin mikä nyt on käytössä.
Jos näin ei ole, saat virheilmoituksen kun yrität ladata asetuksia. Asetukset on tallennettu Ei voitu liittää valittua osiota Ei voitu irroittaa valittua osiota Valittu otsikko:  Haluatko tehdä asetukset BURG:iin eikä grub2:een ? Haluatko tallentaa tekemäsi muutokset? Haluatko valita toisen juuri osion? Muokkaa grub:in esiominaisuuksia Käynnistysrivi Käynnistysvalinta %1 (sijainnin perusteella) Virhe kesken käynnistyslataimen asennusta. Grub Customizer on graafinen liittymä, jolla säädetään grub2/burg asetuksia Grub Customizer: Osioiden valitsin Asenna boot-lataaja MBR:lle sekä asenna
tiedostoja boot-lataajan data-hakemistoon
(jos ne eivät jo ole siellä). Asenna MBR:lle Kiinnitys epäonnistui! Kiinnitä (mount) valittu tiedostojärjestelmä Siirrä alas valittu käynnistysrivi (entry) tai komentosarja Siirrä ylös valittu käynnistysrivi (entry) tai komentosarja Nimeä käynnistysrivi (entry) Käynnityslatainta ei löydy Ei komentosarjaa löydettävissä Osioiden valitsin Ole hyvä, kirjoita laitteen nimi! Esikatselu: Binääristä Proxya ei löydy ! Poista komentosarja asetuksista Tallenna asetukset ja luo uusi  Lisää komentosarja: Sekunnit Valitse _osio... Valitse ja asenna juuri-osio (root partition) Valitse tarvittavat alikiinnityspisteet (submountpoints) Käynnistyslatain on asennettu onnistuneesti Tehty asetus ei ole samanlainen kuin tallennettu asetus käynnistyksessä. Joten se mitä näet nyt, ei ehkä ole samaa kuin mitä näet, kun käynnistät PC:n uudelleen. Korjaa tämä klikkaamalla 'päivitys'! Tallennettu asetus ei ole päivitetty! Nämä ovat kiinnityskohdat fstab -tiedostossasi.
Ole hyvä, välitse jokainen grub/boot:iin liittyvä osio. Tämä vaihtoehto ei toimi, jos "os-prober" komentosarja löytää toisen käyttöjärjestelmän. Kytke pois "%1", jos et tarvitse muita käyttöjärjestelmiä. Tämä ei näytä olevan juuri tiedostojärjestelmä (fstab ei löydy) Aikaraja Saadaksesi yllä olevat värimääritykset toimimaan,
sinun tulee valita taustakuva ! Irroita kiinnitetty tiedostojärjestelmä Valitsit lisävaihtoehdon, jolla valitaan jokin toinen osio.
Huom: Os-prober ei ehkä löydä toimivaa käyttöjärjestelmää. 
Tällöin käynnistä uudelleen Grub Customizer kohdejärjestelmästä käsin 
ja tallenna asetukset (tai käynnistä päivitä-grub/päivitä-borg)
(update-grub/update-burg). Näin saat käynnistysvaihtoehdon käyttöösi. käynnistit Grub Customizer:in live CD:ltä käsin. Näet kaikki käynnistysvaihtoehdot (muokkaamattomat), kun suoritat grubia. Tämä virhe ilmenee (useinmiten), jos et ole asentanut grub customizer:ia oikein. _Lisäasetukset _Laite:  _Muokkaa _Tiedosto _Yleistä _Ohje _Asenna MBR:lle _Lopeta ilman tallentamista _Lopeta ilman päivittämistä _Tallenna ja lopeta _Päivitä ja lopeta _Näytä _käytä jotakin toista osiota:  Lisää tämä käynnistysrivi (entry) uudeksi alavalikoksi taustaväri taustakuva musta sininen ruskea En voi siirtää käynnistysriviä (entry) säädä resoluutio:  syaani vaalean harmaa oletus käynnistysrivi merkkien väri luo toipumiseen käskyrivi vihreä korostettu: asennetaan käynnistyslatainta.. on aktiivinen kernel määritykset nimike vaalean sininen vaalea syaani vaalean harmaa vaalean vihreä vaalea magenta vaalean punainen ladataan asetukset... Etsi toista käyttöjärjestelmää magenta valikon värit nimi normaali: osio esi_valittu:  aiemmin valittu _käynnistysrivi punainen lataa uudelleen asetukset poista tausta Poista tämä käynnistysrivi (entry) nykyisestä alavalikosta asetukset näytä valikko läpinäkyvä tyyppi irroitus epäonnistui! päivitetään asetuksia arvo näkyvyys valkoinen keltainen 