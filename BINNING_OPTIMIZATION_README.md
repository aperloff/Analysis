# Binning Optimization

Fix the Njet-btag binning to what it is by default and play with just sliding the MHT bins first. Recall the default binning is [CMS-SUS-16-033](http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-033/CMS-SUS-16-033_Figure_002.png).

Rishi would start by just plotting the MHT for the background in the MHT bins above but scale to 140 fb<sup>-1</sup> and see how tight the tightest MHT bin is. Then check the same histograms for the control regions like 1-lepton.

Start by using only T1tttt

<ul>
	<li>5 < njet, ht > 500, nb >= 2</li>
	<li> Plot htmiss overlay T1tttt</li>
	<li>Signal points to start with:</li>
	<ul>
		<li>mgluino 2100 mneutralino 100</li>
		<li>Mgluino 1600 mneutalino 1200</li>
	</ul>
</ul>

Important note: This version of the code was forked from a 2016 analysis. It it not the most up-to-date version of the code

## Analysis

The configuration controlling the binning options is [input/input_RA2bin_options.txt](input/input_RA2bin_options.txt). A bin is defined as
```
x>vfloat:RA2Var0Min
x<=vfloat:RA2Var0Max
```

Note: The code won’t allow changing MHT/HT plane for each NJet, NBJet combination

The metric we use to determine that one binning option is better than another is the **Combine tool expected limit**. We only use a few systematics, one signal, and a few backgrounds. This should make the process fairly fast.


<ol>
<li>Make a softlink to the correct binning veriation</li>
```
ln -sf input_RA2bin_options_original.txt input_RA2bin_options.txt
ln -sf input_RA2bin_options_ModifiedNJet_variation1.txt input_RA2bin_options.txt
ln -sf input_RA2bin_options_ModifiedNBJet_variation1.txt input_RA2bin_options.txt
ln -sf input_RA2bin_options_ModifiedMHT_variation1.txt input_RA2bin_options.txt
ln -sf input_RA2bin_options_ModifiedHT_variation1.txt input_RA2bin_options.txt

ln -sf input_selection_original.txt input_selection.txt
ln -sf input_selection_photon_veto.txt input_selection.txt
```

<li>Run MakeAllDCsyst for all mass points in python wrapper</li>

For one mass point:
```
root -b -l -q 'MakeAllDCsyst.C+(1,"T1tttt_900_1_fast","root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan")'
```

For all mass points:
```
python MakeAllDCsystLoop.py -o ModifiedNJet_variation2/ -s T1tttt T1tttt T1qqqq T1qqqq T1bbbb T1bbbb T2tt T2tt T2qq T2qq T2bb T2bb --mass 2100_100 1600_1200 1900_100 1300_1200 2100_100 1600_1300 1100_50 600_500 1500_100 1100_900 1100_100 600_500

python MakeAllDCsystLoop.py -o tmp -s T1bbbb --mass 2100_100

mv tree_syst_T* RA2bin_*  datacards_fast/ModifiedNJet_variation1/
mv tree_syst_T* RA2bin_*  datacards_fast/ModifiedNBJet_variation1/
mv tree_syst_T* RA2bin_*  datacards_fast/ModifiedMHT_variation1/
mv tree_syst_T* RA2bin_*  datacards_fast/ModifiedHT_variation1/
```

You will need to mode the files created to a new folder based on the binning (i.e.):
```
mv RA2bin_*.root RA2bin_*.stdout datacards_fast/ModifiedNJet_variation1/
```

<li>Run MakeAllDCbkg once</li>

```
root -b -l -q 'MakeAllDCBkg.C+(0,"signal,SLe,SLm,LDP,DYe_CleanVars,DYm_CleanVars,GJet_CleanVars","TotalBkg","root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12","datacards_syst/NominalBinning/","nominal","",false)'
```

Makes the MC yields (background) in the signal and control regions. This is the level at which I scan over all of the binning. Some root files need to be hadd’d (the ones with leptons)

Possible regions are:
1. DYe_CleanVars
2. DYm_CleanVars
3. GJet_CleanVars
4. LDP
5. SLe
6. SLm
7. signal 

<br>Run hadd to combine DYe_CleanVars and DYm_CleanVars into DY_CleanVar. Do the same for SLe and SLm into SL.

If running a single region at once, you can use use a loop in bash:
```bash
for reg in "DYe_CleanVars" "DYm_CleanVars" "GJet_CleanVars" "LDP"; do root -b -l -q 'MakeAllDCBkg.C+(0,'$reg',"TotalBkg","root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12","nominal","")'; done
```
This is somewhat obsolete now since the program can for processes and run many regions simultaneously.

Note: Kevin’s version only does the signal region

<details><summary>2016 Results (MC Only)</summary><p>

| Process        | Signal                         | SLe                            | SLm                            | LDP                            | DYe_CleanVars                  | DYm_CleanVars                  | GJets_CleanVars                |
| -------        | ------                         | ---                            | ---                            | ---                            | -------------                  | -------------                  | ---------------                |
| WJet_nominal   | 0.51321762 &plusmn; 0.00143835 | 0.24033249 &plusmn; 0.00097598 | 0.29056606 &plusmn; 0.00107481 | 0.29535592 &plusmn; 0.00094933 | 0.00433467 &plusmn; 0.00009949 | 0.00066043 &plusmn; 0.00004354 | 0.05233416 &plusmn; 0.00044338 |
| TTJets_nominal | 0.21102847 &plusmn; 0.00052053 | 0.10467277 &plusmn; 0.00036811 | 0.13164731 &plusmn; 0.00041229 | 0.13192525 &plusmn; 0.00039899 | 0.03005789 &plusmn; 0.00019657 | 0.03896596 &plusmn; 0.00022448 | 0.02165645 &plusmn; 0.00016645 |
| ZInv_nominal   | 1.24607166 &plusmn; 0.00100598 | 0.00053771 &plusmn; 0.00002003 | 0.00034457 &plusmn; 0.00001449 | 0.28510476 &plusmn; 0.00044162 | 0.00001228 &plusmn; 0.00000271 | 0.00001940 &plusmn; 0.00000373 | 0.00120456 &plusmn; 0.00002733 |
| QCD_nominal    | 0.05960721 &plusmn; 0.00283893 | 0.00001405 &plusmn; 0.00000771 | 0.00025631 &plusmn; 0.00010145 | 2.35495399 &plusmn; 0.01072494 | 0.00387676 &plusmn; 0.00074663 | 0.00287805 &plusmn; 0.00073489 | 0.42458278 &plusmn; 0.00808653 |
| DY_nominal     | 0.00717423 &plusmn; 0.00011186 | 0.00232863 &plusmn; 0.00005535 | 0.00389656 &plusmn; 0.00007438 | 0.00607964 &plusmn; 0.00006359 | 0.19410267 &plusmn; 0.00049386 | 0.23981041 &plusmn; 0.00055084 | 0.00297277 &plusmn; 0.00006943 |

[Integral of events over the 174 bins for 1pb<sup>-1</sup>. The valued are separated into the various signal and control regions and by process.]

</p></details><br\>

<li>Run QuickBkgSystematics once to get all of the bakground histograms</li>

Note: The DY samples were missing from the default version of input/input_sets_DC.txt. Also, only the inclusive TTbar samples was used by default, which has a very low luminosity.
```
python QuickBkgSystematics.py -i datacards_syst/ModifiedNJet_variation1/ -o datacards_syst/ModifiedNJet_variation1/ -l 135000 
```

QuickBkgSystematics.py reads output from MakeAllDBBkg_Rishi, compute the TF, splits the CR in > or < N_min and computes deltaB (either gaussian or poison) as the bin error of a histogram of B

<details><summary>Output 2016 MC</summary><p>
5163.98583984 96.5379094795 <br\>
1560.7265625 72.2693891264 <br\>
99.1667861938 18.3142132199 <br\>
7198.62451172 133.749122745 <br\>
3245.88818359 100.65530181 <br\>
155.114059448 22.6286726269 <br\>
2367.00415039 86.7878522671 <br\>
98.7696533203 17.8166146894 <br\>
323.36428833 32.9350064828 <br\>
15.6547937393 7.57426653589 <br\>
566.453979492 29.459395751 <br\>
154.731750488 21.6973492265 <br\>
11.7572793961 6.05594540789 <br\>
655.262084961 39.9159997063 <br\>
294.371704102 29.5292354488 <br\>
18.399974823 7.50003817781 <br\>
211.900512695 25.0648471968 <br\>
11.4235162735 5.78886594124 <br\>
32.5693893433 9.92530368965 <br\>
1.81411123276 0.084092955062 <br\>
35.6036453247 7.53764162467 <br\>
9.56919670105 5.09198099539 <br\>
0.473349958658 0.0363292169468 <br\>
37.1721687317 10.1954038797 <br\>
15.0247173309 6.16122136057 <br\>
0.793809950352 0.0530221072639 <br\>
10.8868541718 5.73281848411 <br\>
0.429783552885 0.0301648492801 <br\>
1.50151956081 0.080114003623 <br\>
0.0832893103361 0.01589577218 <br\>
6773.78027344 115.078704741 <br\>
4940.3046875 122.043238075 <br\>
469.37399292 35.3147446507 <br\>
5993.18652344 125.421013882 <br\>
7930.78027344 152.71474687 <br\>
674.860961914 42.9287874276 <br\>
3138.75585938 97.4745272012 <br\>
395.967407227 34.0007836855 <br\>
493.340545654 40.1819228178 <br\>
50.6667633057 13.0716100914 <br\>
1634.75158691 50.0897975784 <br\>
978.074462891 46.2696161114 <br\>
97.0199890137 14.5731461373 <br\>
1040.04626465 48.8474136822 <br\>
1386.87402344 57.1359786873 <br\>
135.310913086 18.0111106848 <br\>
475.67590332 35.8349335053 <br\>
70.3141174316 13.6334702975 <br\>
78.45262146 15.3606121729 <br\>
9.45154953003 5.40443342648 <br\>
341.043884277 23.2529432995 <br\>
219.507629395 19.2455304855 <br\>
14.7142791748 5.18049411564 <br\>
152.742645264 18.0483650175 <br\>
264.844787598 22.5438581764 <br\>
19.3019332886 6.17955922398 <br\>
62.9471511841 12.6168918916 <br\>
7.9144077301 4.40182809663 <br\>
8.5478477478 5.02933848479 <br\>
0.965103149414 0.064807596274 <br\>
18.1921215057 5.31493944699 <br\>
13.5118989944 3.63496252824 <br\>
1.211332798 0.219761252028 <br\>
6.84301137924 2.5447424672 <br\>
15.3549699783 5.13597452801 <br\>
1.16699147224 0.138722518561 <br\>
3.15069913864 1.40763229804 <br\>
0.397852659225 0.0265511319188 <br\>
0.354564726353 0.0239277839868 <br\>
0.0434910804033 0.00641077986951 <br\>
675.347412109 33.8635963262 <br\>
1904.72436523 69.6480339025 <br\>
329.196777344 27.5953086226 <br\>
349.24130249 28.5685136737 <br\>
2300.54248047 76.3529401735 <br\>
453.084411621 32.9146535771 <br\>
569.810180664 39.1872501769 <br\>
234.117630005 24.6013807972 <br\>
108.613952637 17.2765976512 <br\>
28.9152145386 8.97948113329 <br\>
356.47076416 20.6005601703 <br\>
867.19329834 34.4185042868 <br\>
112.721893311 13.5340044503 <br\>
122.859680176 14.5311922472 <br\>
841.00592041 37.4913211522 <br\>
141.299301147 16.0973402178 <br\>
152.132705688 18.2295279686 <br\>
64.9757614136 12.0464927429 <br\>
26.1709690094 8.2588580537 <br\>
7.72317361832 4.40371559411 <br\>
132.367294312 12.3407378896 <br\>
374.918670654 19.4819376086 <br\>
31.7811965942 6.10125167619 <br\>
36.1552429199 7.64994816582 <br\>
306.926635742 19.7095975106 <br\>
35.918800354 7.1508573808 <br\>
39.3770103455 8.48552295545 <br\>
15.2755060196 5.46274193467 <br\>
4.94153642654 3.6041780712 <br\>
1.26727199554 0.0769807210458 <br\>
14.2153196335 3.85021983365 <br\>
45.5129508972 6.65463826355 <br\>
3.88531255722 1.10143535752 <br\>
3.50663805008 1.86281807177 <br\>
36.2233848572 6.62781956491 <br\>
4.28145885468 1.33424044264 <br\>
4.30366516113 1.5601242105 <br\>
1.70556807518 0.111626071186 <br\>
0.468825697899 0.037808678486 <br\>
0.126976639032 0.0151806534771 <br\>
244.403778076 22.0410262982 <br\>
109.000320435 15.3140522482 <br\>
230.873687744 22.6117861116 <br\>
127.856422424 15.9740337828 <br\>
44.2431945801 10.5571695134 <br\>
55.0188217163 11.3383265212 <br\>
11.4627075195 5.59154576174 <br\>
7.73925542831 4.22522885415 <br\>
213.75642395 14.5078130597 <br\>
55.0014953613 8.38335759865 <br\>
162.863433838 14.0406620894 <br\>
60.2625427246 9.16093395776 <br\>
20.7741069794 6.03213156841 <br\>
22.9789047241 6.54594947831 <br\>
3.75283002853 0.772630003859 <br\>
2.81292700768 0.6664201211 <br\>
125.24571991 9.98581933466 <br\>
25.2983589172 3.62557471423 <br\>
85.6445617676 8.80421808902 <br\>
25.1534767151 4.93609813941 <br\>
8.17842292786 2.2200599849 <br\>
8.03957462311 1.82159035608 <br\>
1.0313038826 0.119399351563 <br\>
0.741999864578 0.0884903413496 <br\>
24.2249298096 3.92551348255 <br\>
5.19449234009 1.51646173619 <br\>
15.9396715164 3.16327424179 <br\>
5.1002612114 1.41917154786 <br\>
1.45781564713 1.00675435804 <br\>
1.42548680305 0.847088594736 <br\>
0.232262685895 0.0646155764074 <br\>
0.107252955437 0.016626903585 <br\>
14.4247045517 2.33549451694 <br\>
16.7395820618 4.74543703876 <br\>
11.4116439819 3.80833787368 <br\>
21.4902153015 6.01387336713 <br\>
2.03932666779 0.699588677224 <br\>
7.42399501801 3.87287044646 <br\>
0.73983258009 0.116704736598 <br\>
1.19885337353 0.368476720791 <br\>
21.7172660828 3.3291230057 <br\>
16.1002483368 2.98794225218 <br\>
15.3760976791 2.87562190207 <br\>
15.4737014771 2.3537256336 <br\>
1.29593133926 0.676013049609 <br\>
4.43248176575 1.10019595799 <br\>
0.406513929367 0.0995367643642 <br\>
0.651877820492 0.103288819126 <br\>
14.8513631821 2.81086136699 <br\>
9.69581317902 2.17029825507 <br\>
11.1223926544 2.57618015752 <br\>
8.66739559174 1.97085777234 <br\>
0.65918058157 0.139171109139 <br\>
2.0630030632 0.954476170621 <br\>
0.168103009462 0.0657798142283 <br\>
0.243593275547 0.0593957326824 <br\>
3.67556333542 1.3926934114 <br\>
3.12044692039 1.2036878641 <br\>
2.88443589211 1.22651853676 <br\>
2.04032087326 0.979915191307 <br\>
0.164622664452 0.0597418922543 <br\>
0.543538630009 0.117495603179 <br\>
0.0373050794005 0.0164195240007 <br\>
0.0571966841817 0.0156788438711
</p></details>

<li>Make datacards for each mass point (will make 174 cards for each bin) and then combine them into one datacard per mass point. Will also run combine by default.</li>

```
python BuildDataCards.py
python BuildDataCards.py -i datacards_fast/ModifiedNJet_variation1/ -j datacards_syst/ModifiedNJet_variation1/ -o datacards/ModifiedNJet_variation1/ -l 135000.0 -m T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq --mass 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 -r
python BuildDataCards.py -i datacards_fast/ModifiedNBJet_variation1/ -j datacards_syst/ModifiedNBJet_variation1/ -o datacards/ModifiedNBJet_variation1/ -l 135000.0 -m T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq --mass 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 -r
python BuildDataCards.py -i datacards_fast/ModifiedMHT_variation1/ -j datacards_syst/ModifiedMHT_variation1/ -o datacards/ModifiedMHT_variation1/ -l 135000.0 -m T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq --mass 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 -r
python BuildDataCards.py -i datacards_fast/ModifiedHT_variation1/ -j datacards_syst/ModifiedHT_variation1/ -o datacards/ModifiedHT_variation1/ -l 135000.0 -m T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq --mass 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 -r

python BuildDataCards.py -i datacards_fast/ModifiedNJet_variation2/ -j datacards_syst/ModifiedNJet_variation2/ -o datacards/ModifiedNJet_variation2/ -l 135000.0 -m T1tttt T1tttt T1bbbb T1bbbb T1qqqq T1qqqq T2tt T2tt T2bb T2bb T2qq T2qq --mass 2100_100 1600_1200 2100_100 1600_1300 1900_100 1300_1200 1100_50 600_500 1100_100 600_500 1500_100 1100_900 -r -n 12
```

To print the limits in some systematic fashion:
```
python WPTable.py -i datacards/ModifiedNJet_variation2/ -M T1tttt T1tttt T1bbbb T1bbbb T1qqqq T1qqqq T2tt T2tt T2bb T2bb T2qq T2qq -m 2100_100 1600_1200 2100_100 1600_1300 1900_100 1300_1200 1100_50 600_500 1100_100 600_500 1500_100 1100_900 --combine_result --sig -d T1tttt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt T1bbbb=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt T1qqqq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt T2tt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2.txt T2bb=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2.txt T2qq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2qq.txt
```
</ol>


## Optimization Targets
Optimize T2qq, T1qqqq, T1tttt, T2tt:

&nbsp;&nbsp;&nbsp;&nbsp;Optimize NJets and btags: Pick m<sub>&#x0067; &#x0303;</sub> m<sub>&chi;<sub>1</sub></sub> point for low and high NJets.

&nbsp;&nbsp;&nbsp;&nbsp;Keep HT/MHT binning the same as last time

Optimize T1qqqq (maybe look at T2qq):

&nbsp;&nbsp;&nbsp;&nbsp;i.e. Run scan on m<sub>gtilde</sub>=1900 and m_chi1=100 (tightest MHT/HT threshold)

&nbsp;&nbsp;&nbsp;&nbsp;also run on m_<sub>&#x0067; &#x0303;</sub>=1300 and m<sub>&chi;</sub>=1200 (loosest MHT/HT threshold)

&nbsp;&nbsp;&nbsp;&nbsp;Fix the new NJet/NBtag binning

## Notes
Rishi’s area: /uscms_data/d2/rgp230/RA2LegacyOptimization/RA2Nominal/CMSSW_8_0_25/src/Analysis/ (datacards_syst/)

Alexx's area: /uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc6/CMSSW_8_0_25/src/Analysis/

35900 is to scale to 2016 luminosity because already scaled to 1 pb<sup>-1</sup>

(RISHI GIVES FULL REIN FOR ALEXX TO EDIT THIS CODE)

## To-Do
<ol>
<li>Look into is why your observed value and expected value (50% CL) are different.</br>
Check if the observed number in your datacards actually adds up to the sum of the background yields. It should. --> It does</br>
If it does, then next check a single card test to see if observed and expected are the same. --> Within 0.1% in most cases (found one with 9% difference), but not exactly the same</br>
Then try adding two cards and check again. --> Still off, even for cases with all backgrounds non-zero</li>
<li>Improve writing of ```vuint:RA2VarXBins``` arrays</li>
<li>Make capable of scanning over multiple “datacard_syst” folders or multiple suffixes (multiple binning cases)</li>
<li>Make bottom panel with S/sqrt(B)</li>
<li>Run through once all code + combine and check how long it takes --> 7 minutes for combine</li>
<li>Need to look up the expected cross sections for a given gluino mass point to convert to pb</li>
<li>Scale the flat/assumed uncertainties with luminosity</li>
<li>Make difference in exclusion plots between published an non-published plots</li>

Note: If it takes too long (>30 min w/asymptotic limits and all syst), find the bottleneck (reduce nuisances). Maybe sum backgrounds and take biggest nuisance instead of one per background.
</ol>




## Limit Comparisons

Test single bin limit for expected/observed matching:
combine -M AsymptoticLimits card_searchbin100.txt -n T1tttt_2100_100 -S 0 -t -1
no systematics included
method used is AsymptoticLimits
Computing results starting from expected outcome (a-priori)
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 36.4061
Expected  2.5%: r < 16.0562
Expected 16.0%: r < 23.1995
Expected 50.0%: r < 36.3750
Expected 84.0%: r < 58.9938
Expected 97.5%: r < 92.4644

combine -M AsymptoticLimits card_searchbin100.txt -n T1tttt_2100_100 -S 0
no systematics included
method used is AsymptoticLimits
Computing results starting from observation (a-posteriori)
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 36.4061
Expected  2.5%: r < 16.0562
Expected 16.0%: r < 23.1995
Expected 50.0%: r < 36.3750
Expected 84.0%: r < 58.9938
Expected 97.5%: r < 92.4644

36.4061/36.3750 = 1.0008549828

 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 37.7553
Expected  2.5%: r < 15.0938
Expected 16.0%: r < 21.9163
Expected 50.0%: r < 34.5000
Expected 84.0%: r < 56.5030
Expected 97.5%: r < 89.0261





gluino-gluino cross sections (sigma) @ 13 TeV:
	mgluino=2100: 0.000591918 pb = 0.59 fb
	mgluino=1600:  0.00810078 pb = 8.1 fb

@35900 pb-1
===========
T1tttt_2100_100
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 1.7729
Expected  2.5%: r < 0.5143
Expected 16.0%: r < 0.7743
Expected 50.0%: r < 1.2539
Expected 84.0%: r < 2.0736
Expected 97.5%: r < 3.2558

T1tttt_1600_1200
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 1.7158
Expected  2.5%: r < 0.6016
Expected 16.0%: r < 0.8641
Expected 50.0%: r < 1.3164
Expected 84.0%: r < 2.0353
Expected 97.5%: r < 2.9961

Simplified projections give:
	mgluino=2100 expected sigma limit = 0.59 fb * 1.25 = 0.74 fb
	mgluino=1600 expected sigma limit = 8.1 fb * 1.32 = 10.7 fb

From SUS-16-033/AN/2016-350:
	mgluino=2100 mneutralino=100  expected sigma limit: 0.000811354 pb = 0.81 fb
	mgluino=1600 mneutralino=1200 expected sigma limit: 0.0162880 pb = 16.3 fb


@135000 pb-1
============
T1tttt_2100_100
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 0.6356
Expected  2.5%: r < 0.2190
Expected 16.0%: r < 0.3212
Expected 50.0%: r < 0.5098
Expected 84.0%: r < 0.8227
Expected 97.5%: r < 1.2546

T1tttt_1600_1200
 -- AsymptoticLimits ( CLs ) --
Observed Limit: r < 0.7359
Expected  2.5%: r < 0.3157
Expected 16.0%: r < 0.4397
Expected 50.0%: r < 0.6465
Expected 84.0%: r < 0.9609
Expected 97.5%: r < 1.3652

Simplified projections give:
	mgluino=2100 expected sigma limit = 0.59 fb * 0.5098 = 0.300782 fb
	mgluino=1600 expected sigma limit = 8.1 fb * 0.6465 = 5.23665 fb

0.5098/1.25 = 0.408
35.9/135.10 = 0.2659259259 
sqrt(35.9/135) = 0.5156800616 


Variation 2:
NB: 0, 1, 2-3, >=4
NJet: 2-3, 4-5, 6-7, 8-10, >=11
MHT: 300-350, 350-700, 700-950, >=950
HT:  
HT5/HT vs DeltaPhi
Photon Veto
MHT(jets |eta|<2.4) - Redo DeltaPhi for 4 leading jets
HT-Centrality = HT(|eta|<1.5)/HT(|eta|<2.4)

Variation 3:
MHT: 300-400, 400-500, 500-750, >=750

Variation 4:
MHT: 300-350, 350-600, 600-750, >=750