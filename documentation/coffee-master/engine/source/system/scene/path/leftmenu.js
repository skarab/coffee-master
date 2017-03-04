function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6408\" class=\"headerLeftMenuInActive\"><a id=\"aID6408\" href=\"#\" OnMouseOver=\"link('_dir','path0',this)\" class=\"leftMenuLinkHeadInActive\">path</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID929\" class=\"leftMenuInActive\"><a id=\"aID929\" href=\"#\" OnMouseOver=\"link('_class','Path42087',this)\" class=\"leftMenuLinkInActive\">Path</a></div>\n");
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
