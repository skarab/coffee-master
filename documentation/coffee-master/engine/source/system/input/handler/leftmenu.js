function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6389\" class=\"headerLeftMenuInActive\"><a id=\"aID6389\" href=\"#\" OnMouseOver=\"link('_dir','handler0',this)\" class=\"leftMenuLinkHeadInActive\">handler</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID899\" class=\"leftMenuInActive\"><a id=\"aID899\" href=\"#\" OnMouseOver=\"link('_class','Handler26233',this)\" class=\"leftMenuLinkInActive\">Handler</a></div>\n");
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
