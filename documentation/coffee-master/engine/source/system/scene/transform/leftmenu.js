function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6410\" class=\"headerLeftMenuInActive\"><a id=\"aID6410\" href=\"#\" OnMouseOver=\"link('_dir','transform0',this)\" class=\"leftMenuLinkHeadInActive\">transform</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID932\" class=\"leftMenuInActive\"><a id=\"aID932\" href=\"#\" OnMouseOver=\"link('_class','Transform42087',this)\" class=\"leftMenuLinkInActive\">Transform</a></div>\n");
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
