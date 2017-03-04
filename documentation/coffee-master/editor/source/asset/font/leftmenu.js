function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6469\" class=\"headerLeftMenuInActive\"><a id=\"aID6469\" href=\"#\" OnMouseOver=\"link('_dir','font0',this)\" class=\"leftMenuLinkHeadInActive\">font</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1052\" class=\"leftMenuInActive\"><a id=\"aID1052\" href=\"#\" OnMouseOver=\"link('_class','FontFNT22463',this)\" class=\"leftMenuLinkInActive\">FontFNT</a></div>\n");
document.write("<div id=\"divID1053\" class=\"leftMenuInActive\"><a id=\"aID1053\" href=\"#\" OnMouseOver=\"link('_class','FontTTF22463',this)\" class=\"leftMenuLinkInActive\">FontTTF</a></div>\n");
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
