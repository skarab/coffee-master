function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6473\" class=\"headerLeftMenuInActive\"><a id=\"aID6473\" href=\"#\" OnMouseOver=\"link('_dir','sound0',this)\" class=\"leftMenuLinkHeadInActive\">sound</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1066\" class=\"leftMenuInActive\"><a id=\"aID1066\" href=\"#\" OnMouseOver=\"link('_class','SoundOGG22463',this)\" class=\"leftMenuLinkInActive\">SoundOGG</a></div>\n");
document.write("<div id=\"divID1067\" class=\"leftMenuInActive\"><a id=\"aID1067\" href=\"#\" OnMouseOver=\"link('_class','SoundWAV22463',this)\" class=\"leftMenuLinkInActive\">SoundWAV</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
