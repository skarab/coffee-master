function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6331\" class=\"headerLeftMenuInActive\"><a id=\"aID6331\" href=\"#\" OnMouseOver=\"link('_dir','data0',this)\" class=\"leftMenuLinkHeadInActive\">data</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID825\" class=\"leftMenuInActive\"><a id=\"aID825\" href=\"#\" OnMouseOver=\"link('_class','Data35340',this)\" class=\"leftMenuLinkInActive\">Data</a></div>\n");
document.write("<div id=\"divID826\" class=\"leftMenuInActive\"><a id=\"aID826\" href=\"#\" OnMouseOver=\"link('_class','Stream35340',this)\" class=\"leftMenuLinkInActive\">Stream</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6224\" class=\"leftMenuInActive\"><a id=\"aID6224\" href=\"#\" OnMouseOver=\"link('_member','MODE1371500270',this)\" class=\"leftMenuLinkInActive\">MODE</a></div>\n");
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
