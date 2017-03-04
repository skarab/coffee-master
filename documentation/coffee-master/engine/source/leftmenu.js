function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6263\" class=\"headerLeftMenuInActive\"><a id=\"aID6263\" href=\"#\" OnMouseOver=\"link('_dir','source0',this)\" class=\"leftMenuLinkHeadInActive\">source</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6510\" class=\"leftMenuInActive\"><a id=\"aID6510\" href=\"#\" OnMouseOver=\"link('_dir','kernel/kernel0',this)\" class=\"leftMenuLinkInActive\">kernel</a></div>\n");
document.write("<div id=\"divID6503\" class=\"leftMenuInActive\"><a id=\"aID6503\" href=\"#\" OnMouseOver=\"link('_dir','system/system0',this)\" class=\"leftMenuLinkInActive\">system</a></div>\n");
document.write("<div id=\"divID6508\" class=\"leftMenuInActive\"><a id=\"aID6508\" href=\"#\" OnMouseOver=\"link('_dir','wide/wide0',this)\" class=\"leftMenuLinkInActive\">wide</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID723\" class=\"leftMenuInActive\"><a id=\"aID723\" href=\"#\" OnMouseOver=\"link('_class','Engine3886',this)\" class=\"leftMenuLinkInActive\">Engine</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6207\" class=\"leftMenuInActive\"><a id=\"aID6207\" href=\"#\" OnMouseOver=\"link('_member','RUN_MODE50712',this)\" class=\"leftMenuLinkInActive\">RUN_MODE</a></div>\n");
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
