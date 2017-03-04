function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6330\" class=\"headerLeftMenuInActive\"><a id=\"aID6330\" href=\"#\" OnMouseOver=\"link('_dir','thread0',this)\" class=\"leftMenuLinkHeadInActive\">thread</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID821\" class=\"leftMenuInActive\"><a id=\"aID821\" href=\"#\" OnMouseOver=\"link('_class','Locker41582',this)\" class=\"leftMenuLinkInActive\">Locker</a></div>\n");
document.write("<div id=\"divID822\" class=\"leftMenuInActive\"><a id=\"aID822\" href=\"#\" OnMouseOver=\"link('_class','Mutex41582',this)\" class=\"leftMenuLinkInActive\">Mutex</a></div>\n");
document.write("<div id=\"divID823\" class=\"leftMenuInActive\"><a id=\"aID823\" href=\"#\" OnMouseOver=\"link('_class','Thread41582',this)\" class=\"leftMenuLinkInActive\">Thread</a></div>\n");
document.write("<div id=\"divID824\" class=\"leftMenuInActive\"><a id=\"aID824\" href=\"#\" OnMouseOver=\"link('_class','ThreadedObject41503',this)\" class=\"leftMenuLinkInActive\">ThreadedObject<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1310\" class=\"leftMenuInActive\"><a id=\"aID1310\" href=\"#\" OnMouseOver=\"link('_member','ThreadedObject18069215',this)\" class=\"leftMenuLinkInActive\">ThreadedObject</a></div>\n");
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
